#include "stdafx.h"
#include "ApiManager.h"


void ApiManager::SetServerIP(std::string ip)
{
	if (!m_http->SetAddress(ip)) {
		throw std::invalid_argument("Invalid server socket IP");
	}
}

void ApiManager::SetServerIP(HttpClient::IpAddr ip)
{
	if (!m_http->SetAddress(ip)) {
		throw std::invalid_argument("Invalid server socket IP");
	}
}

void ApiManager::SetServerPort(unsigned int port)
{
	if (!m_http->SetPort(port)) {
		throw std::invalid_argument("Invalid server socket Port");
	}
}

void ApiManager::SetServerSubURI(std::string uri)
{
	if (!m_http->SetSubURI(uri)) {
		throw std::invalid_argument("Invalid subURI string");
	}
}

ApiManager::ApiManager()
{
	m_railWay = new RailWay();
	m_http = new HttpClient();
}


ApiManager::~ApiManager()
{
	delete m_railWay;
	delete m_http;
}

std::string ApiManager::ServerGet(HttpClient::Command com)
{
	return m_http->GetData(HttpClient::Request(com));
}

std::string ApiManager::ServerGet(HttpClient::Command com, int id)
{
	return m_http->GetData(HttpClient::Request(com, id));
}

bool ApiManager::ServerPut(HttpClient::Command com, std::string payload)
{
	return m_http->SetData(HttpClient::Request(com),payload);
}

bool ApiManager::ServerPut(HttpClient::Command com, int id, std::string payload)
{
	return m_http->SetData(HttpClient::Request(com,id), payload);
}
