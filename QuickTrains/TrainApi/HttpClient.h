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

	enum Command {
		BLOKY,
		BLOKSTAV,
		LOKS,
		LOKSTAV
	};

	struct Request {
		Command com;
		int id;
		Request(Command c) {
			com = c;
		}
		Request(Command c, int i) {
			com = c;
			id = i;
		}
	};

	HttpClient();
	~HttpClient();

	bool SetAddress(IpAddr address);
	bool SetAddress(std::string address);
	bool SetPort(int port);
	bool SetSubURI(std::string uri);
	std::string GetData(Request Q);
	bool SetData(Request Q, std::string data);

private:
	IpAddr m_serverAddress;
	unsigned int m_port;
	std::string m_subURI;

	bool CheckAddress(IpAddr address);
	IpAddr GatherAddress(std::string address);
};

