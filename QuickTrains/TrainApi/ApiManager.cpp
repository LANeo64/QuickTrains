#include "stdafx.h"
#include "ApiManager.h"


void ApiManager::SetServer(std::string server)
{
	if (!m_http->SetHost(server)) {
		throw std::invalid_argument("Invalid server IP or hostname");
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

void ApiManager::SetHotApi(bool state)
{
	m_apiHotMode = state;
}

ApiManager::ApiManager()
{
	m_railWay = new RailWay();
	m_http = new HttpClient();
	m_apiHotMode = true;
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
