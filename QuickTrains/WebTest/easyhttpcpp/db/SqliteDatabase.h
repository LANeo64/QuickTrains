/*
 * Copyright 2017 Sony Corporation
 */

#ifndef EASYHTTPCPP_DB_SQLITEDATABASE_H_INCLUDED
#define EASYHTTPCPP_DB_SQLITEDATABASE_H_INCLUDED

#include <string>
#include <vector>

#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"

#include "easyhttpcpp/db/SqliteCursor.h"

namespace easyhttpcpp {
namespace db {

class ContentValues;

class SqliteDatabase : public Poco::RefCountedObject {
public:
    typedef long long RowId;
    typedef Poco::AutoPtr<SqliteDatabase> Ptr;

    enum AutoVacuum {
        // 0 means disable auto vacuum
        AutoVacuumNone,
        // 1 means enable full auto vacuum
        AutoVacuumFull,
        // 2 means enable incremental vacuum
        AutoVacuumIncremental
    };

    virtual ~SqliteDatabase();

    static SqliteDatabase::Ptr openOrCreateDatabase(const std::string& path);

    virtual void execSql(const std::string& sql);

    virtual SqliteCursor::Ptr query(const std::string& table, const std::vector<std::string>* columns,
            const std::string* selection, const std::vector<std::string>* selectionArgs, const std::string* groupBy,
            const std::string* having, const std::string* orderBy, const std::string* limit,
            const bool distinct = true);

    virtual SqliteCursor::Ptr rawQuery(const std::string& sql, const std::vector<std::string>* selectionArgs);

    virtual RowId insert(const std::string& table, const ContentValues& values);

    virtual RowId replace(const std::string& table, const ContentValues& initialValues);

    virtual size_t deleteRows(const std::string& table, const std::string* whereClause,
            const std::vector<std::string>* whereArgs);

    virtual size_t update(const std::string& table, const ContentValues& values,
            const std::string* whereClause, const std::vector<std::string>* whereArgs);

    virtual void beginTransaction();

    virtual void endTransaction();

    virtual void setTransactionSuccessful();

    virtual void close();

    virtual unsigned int getVersion();

    virtual void setVersion(unsigned int version);

    virtual AutoVacuum getAutoVacuum();

    virtual void setAutoVacuum(AutoVacuum autoVacuum);

    virtual bool isOpen();

    virtual void reopen();

private:
    Poco::SharedPtr<Poco::Data::Session> m_pSession;
    Poco::FastMutex m_mutex;

    bool m_opened;

    SqliteDatabase(const std::string& path);
    void throwExceptionIfIllegalState();
};

} /* namespace db */
} /* namespace easyhttpcpp */

#endif /* EASYHTTPCPP_DB_SQLITEDATABASE_H_INCLUDED */
