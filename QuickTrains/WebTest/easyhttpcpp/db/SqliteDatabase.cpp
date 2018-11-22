/*
 * Copyright 2017 Sony Corporation
 */

#include "Poco/Any.h"
#include "Poco/Delegate.h"
#include "Poco/Exception.h"
#include "Poco/SharedPtr.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/SQLite/Notifier.h"

#include "easyhttpcpp/common/CoreLogger.h"
#include "easyhttpcpp/common/StringUtil.h"
#include "easyhttpcpp/db/ContentValues.h"
#include "easyhttpcpp/db/SqlException.h"
#include "easyhttpcpp/db/SqliteDatabase.h"
#include "easyhttpcpp/db/SqliteQueryBuilder.h"

using easyhttpcpp::common::StringUtil;

namespace easyhttpcpp {
namespace db {

static const std::string Tag = "SqliteDatabase";

SqliteDatabase::SqliteDatabase(const std::string& path) : m_opened(false)
{
    if (path.empty()) {
        EASYHTTPCPP_LOG_D(Tag, "Database file path is not set");
        throw SqlIllegalStateException("Can't create database. Please set the database file path.");
    }

    try {
        m_pSession = new Poco::Data::Session("SQLite", path);
        // TODO can we use Session#isConnected?
        m_opened = true;
    } catch (const Poco::Exception& e) {
        EASYHTTPCPP_LOG_D(Tag, "Failed to create Session %s", e.message().c_str());
        throw SqlIllegalStateException("Failed to create database", e);
    }
}

SqliteDatabase::~SqliteDatabase()
{
    if (m_pSession) {
        // TODO session throws exception in destructor; nothrow delete flag??
        m_pSession = NULL;
    }
    m_opened = false;
}

SqliteDatabase::Ptr SqliteDatabase::openOrCreateDatabase(const std::string& path)
{
    return new SqliteDatabase(path);
}

void SqliteDatabase::execSql(const std::string& sql)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);

    try {
        Poco::Data::Statement statement(*m_pSession);
        statement << sql;
        statement.execute();
    } catch (const Poco::Exception& e) {
        EASYHTTPCPP_LOG_D(Tag, "Failed to execute sql %s", e.message().c_str());
        throw SqlExecutionException("Failed to execute sql " + sql, e);
    }
}

SqliteCursor::Ptr SqliteDatabase::query(const std::string& table, const std::vector<std::string>* columns,
        const std::string* selection, const std::vector<std::string>* selectionArgs,
        const std::string* groupBy, const std::string* having, const std::string* orderBy,
        const std::string* limit, const bool distinct)
{
    std::string sql = SqliteQueryBuilder::buildQueryString(table, columns, selection, groupBy, having, orderBy, limit,
            distinct);

    return rawQuery(sql, selectionArgs);
}

SqliteCursor::Ptr SqliteDatabase::rawQuery(const std::string& sql, const std::vector<std::string>* selectionArgs)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);

    try {
        Poco::Data::Statement statement(*m_pSession);
        statement << sql;

        if (selectionArgs) {
            int count = selectionArgs->size();
            for (int index = 0; index < count; index++) {
                std::string selection = selectionArgs->at(index);
                statement, Poco::Data::Keywords::bind(selection);
            }
        }

        statement.execute();

        return new SqliteCursor(statement);
    } catch (const Poco::Exception& e) {
        EASYHTTPCPP_LOG_D(Tag, "Failed to query %s", e.message().c_str());
        throw SqlExecutionException("query failed", e);
    }
}

SqliteDatabase::RowId SqliteDatabase::insert(const std::string& table, const ContentValues& values)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);

    try {
        Poco::Data::SQLite::Notifier notifier(*m_pSession, Poco::Data::SQLite::Notifier::SQLITE_NOTIFY_UPDATE);
        std::string sql = SqliteQueryBuilder::buildInsertString(table, values, SqliteConflictAlgorithmNone);
        Poco::Data::Statement statement(*m_pSession);
        statement << sql;
        statement.execute();

        Poco::Int64 rowId = notifier.getRow();
        return rowId;
    } catch (const Poco::Exception& e) {
        EASYHTTPCPP_LOG_D(Tag, "insert failed %s", e.message().c_str());
        throw SqlExecutionException("Failed to insert", e);
    }
}

SqliteDatabase::RowId SqliteDatabase::replace(const std::string& table, const ContentValues& initialValues)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);

    try {
        Poco::Data::SQLite::Notifier notifier(*m_pSession, Poco::Data::SQLite::Notifier::SQLITE_NOTIFY_UPDATE);

        std::string sql = SqliteQueryBuilder::buildInsertString(table, initialValues, SqliteConflictAlgorithmReplace);
        Poco::Data::Statement statement(*m_pSession);
        statement << sql;
        statement.execute();

        Poco::Int64 rowId = notifier.getRow();
        return rowId;
    } catch (const Poco::Exception& e) {
        EASYHTTPCPP_LOG_D(Tag, "replace failed %s", e.message().c_str());
        throw SqlExecutionException("Failed to replace", e);
    }
}

size_t SqliteDatabase::deleteRows(const std::string& table, const std::string* whereClause,
        const std::vector<std::string>* whereArgs)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    try {
        std::string sql = SqliteQueryBuilder::buildDeleteString(table, whereClause);
        Poco::Data::Statement statement(*m_pSession);
        statement << sql;

        if (whereArgs) {
            int count = whereArgs->size();
            for (int index = 0; index < count; index++) {
                std::string where = whereArgs->at(index);
                statement, Poco::Data::Keywords::bind(where);
            }
        }

        return statement.execute();
    } catch (const Poco::Exception& e) {
        EASYHTTPCPP_LOG_D(Tag, "delete failed %s", e.message().c_str());
        throw SqlExecutionException("Failed to delete", e);
    }
}

size_t SqliteDatabase::update(const std::string& table, const ContentValues& values,
        const std::string* whereClause, const std::vector<std::string>* whereArgs)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    try {
        // validity check of values is performed in SqliteQueryBuilder::buildUpdateString

        std::string sql = SqliteQueryBuilder::buildUpdateString(table, values, whereClause,
                SqliteConflictAlgorithmNone);
        Poco::Data::Statement statement(*m_pSession);
        statement << sql;

        if (whereArgs) {
            int count = whereArgs->size();
            for (int index = 0; index < count; index++) {
                std::string where = whereArgs->at(index);
                statement, Poco::Data::Keywords::bind(where);
            }
        }

        return statement.execute();
    } catch (const Poco::Exception& e) {
        EASYHTTPCPP_LOG_D(Tag, "update failed %s", e.message().c_str());
        throw SqlExecutionException("Failed to update", e);
    }
}

void SqliteDatabase::close()
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    // TODO consume and not throw?
    throwExceptionIfIllegalState();
    if (m_pSession->isTransaction()) {
        std::string msg = "Can not close database, because database is in transaction";
        EASYHTTPCPP_LOG_D(Tag, msg.c_str());
        throw SqlIllegalStateException(msg);
    }
    m_opened = false;
}

void SqliteDatabase::beginTransaction()
{
    throwExceptionIfIllegalState();
    try {
        m_pSession->begin();
    } catch (const Poco::Exception& e) {
        EASYHTTPCPP_LOG_D(Tag, "catch Exception in beginTransaction %s", e.message().c_str());
        throw SqlIllegalStateException("Can't begin transaction", e);
    }
}

void SqliteDatabase::endTransaction()
{
    throwExceptionIfIllegalState();
    try {
        if (m_pSession->isTransaction()) {
            m_pSession->rollback();
        }
    } catch (const Poco::Exception& e) {
        EASYHTTPCPP_LOG_D(Tag, "catch Exception in endTransaction %s", e.message().c_str());
        throw SqlIllegalStateException("Can't end transaction", e);
    }
}

void SqliteDatabase::setTransactionSuccessful()
{
    throwExceptionIfIllegalState();
    try {
        m_pSession->commit();
    } catch (const Poco::Exception& e) {
        EASYHTTPCPP_LOG_D(Tag, "catch Exception in setTransactionSuccessful %s", e.message().c_str());
        throw SqlIllegalStateException("Can't set transaction successful", e);
    }
}

unsigned int SqliteDatabase::getVersion()
{
    throwExceptionIfIllegalState();
    std::string sql = "PRAGMA user_version;";

    SqliteCursor::Ptr pCursor = rawQuery(sql, NULL);
    return pCursor->getInt(0);
}

void SqliteDatabase::setVersion(unsigned int version)
{
    throwExceptionIfIllegalState();
    std::string sql = StringUtil::format("PRAGMA user_version = %d;", version);
    execSql(sql);
}

SqliteDatabase::AutoVacuum SqliteDatabase::getAutoVacuum()
{
    throwExceptionIfIllegalState();
    std::string sql = "PRAGMA auto_vacuum;";

    SqliteCursor::Ptr pCursor = rawQuery(sql, NULL);
    return static_cast<SqliteDatabase::AutoVacuum>(pCursor->getInt(0));
}

void SqliteDatabase::setAutoVacuum(AutoVacuum autoVacuum)
{
    throwExceptionIfIllegalState();
    std::string sql = StringUtil::format("PRAGMA auto_vacuum = %d;", autoVacuum);
    execSql(sql);
}

bool SqliteDatabase::isOpen()
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    return m_opened;
}

void SqliteDatabase::reopen()
{
    try {
        m_pSession->close();
        m_pSession->open();
        m_opened = true;
    } catch (const Poco::Exception& e) {
        EASYHTTPCPP_LOG_D(Tag, "Failed to reopen %s", e.message().c_str());
        throw SqlIllegalStateException("Can not open database", e);
    }
}

void SqliteDatabase::throwExceptionIfIllegalState()
{
    if (!m_pSession || !m_opened) {
        EASYHTTPCPP_LOG_D(Tag, "Can not continue processing because of illegal state");
        throw SqlIllegalStateException("SqliteDatabase Session is not created");
    }
}
} /* namespace db */
} /* namespace easyhttpcpp */
