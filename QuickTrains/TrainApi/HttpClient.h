#pragma once

#include <vector>
#include <regex>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>

#include "Utils.h"

using boost::asio::ip::tcp;

class HttpClient
{
public:
	enum Encryption {
		AUTO,
		HTTP,
		HTTPS
	};

	enum ConnectionMode {
		SINGLE,
		BURST
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
	HttpClient(std::string host);
	HttpClient(std::string host, int port, Encryption enc = AUTO);
	HttpClient(std::string host, int port, std::string subURI, Encryption enc = AUTO);
	~HttpClient();

	bool SetHost(std::string host);
	bool SetPort(int port);
	bool SetSubURI(std::string uri);
	std::string GetData(Request Q, ConnectionMode mode = SINGLE);
	bool SetData(Request Q, std::string json, ConnectionMode mode = SINGLE);
	int Test();
	int Test2();

private:
	std::string m_host;
	unsigned int m_port;
	std::string m_subURI;
	std::string m_lastError;
	Encryption m_encryption;

	//boost::asio::io_context m_io_context;
	//tcp::resolver& resolver;

	bool CheckAddress(std::string address);
	bool CheckName(std::string server);
	bool CheckSubURI(std::string uri);

	//bool Connect();
	//bool IsConnected();
	//bool Disconnect();
};

