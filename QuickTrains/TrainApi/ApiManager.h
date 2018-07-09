#pragma once

#include <stdexcept>

#include "RailWay.h"
#include "HttpClient.h"
#include "QuickJSON.h"

class ApiManager
{
public:
	static ApiManager& GetApi() {
		static ApiManager s;
		return s;
	}

	void SetServerIP(std::string ip);
	void SetServerIP(HttpClient::IpAddr ip);
	void SetServerPort(unsigned int port);
	std::string ServerGet(std::string url);
	int ServerPut(std::string url, std::string payload);

private:
	ApiManager();
	~ApiManager();

	RailWay* m_railWay;
	HttpClient* m_http;
};
