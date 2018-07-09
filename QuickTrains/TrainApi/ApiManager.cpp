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
