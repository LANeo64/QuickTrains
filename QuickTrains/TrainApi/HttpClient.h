#pragma once

#include <vector>

#include "Utils.h"

class HttpClient
{
public:
	struct IpAddr {
		unsigned int A;
		unsigned int B;
		unsigned int C;
		unsigned int D;
	};

	HttpClient();
	~HttpClient();

	bool SetAddress(IpAddr address);
	bool SetAddress(std::string address);
	bool SetPort(int port);

private:
	IpAddr m_serverAddress;
	unsigned int m_port;

	bool CheckAddress(IpAddr address);
	IpAddr GatherAddress(std::string address);
};

