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
	struct IpAddr {
		unsigned int A;
		unsigned int B;
		unsigned int C;
		unsigned int D;

		IpAddr() {
			A = 0;
			B = 0;
			C = 0;
			D = 0;
		}

		IpAddr(std::string addr) {
			int len = addr.length();
			int pos = 0;
			int byte = 4;
			char num;
			for (int i = len-1; i >= 0; i--) {
				num = addr[i];
				if (num == '.') {
					byte--;
					pos = 0;
				} else {
					switch (byte)
					{
					case 1: A = ((int)num - 48)*(10 ^ pos); break;
					case 2: B = ((int)num - 48)*(10 ^ pos); break;
					case 3: C = ((int)num - 48)*(10 ^ pos); break;
					case 4: D = ((int)num - 48)*(10 ^ pos); break;
					default:
						throw std::exception("Illegal character found in IP conversion!");
						break;
					}
					pos++;
				}
			}
		}
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

	static bool IsIp(std::string str) {
		std::regex ip4pattern("\\d{1,3}(\\.\\d{1,3}){3})");
		if (std::regex_match(str, ip4pattern)) {
			return true;
		} else {
			return false;
		}
	}

	HttpClient();
	~HttpClient();

	bool SetHost(std::string host);
	bool SetPort(int port);
	bool SetSubURI(std::string uri);
	bool Connect(ConnectionMode mode = SINGLE);
	bool Disconnect();
	std::string GetData(Request Q);
	bool SetData(Request Q, std::string data);

private:
	std::string m_host;
	std::string m_serverName;
	IpAddr m_serverAddress;
	unsigned int m_port;
	std::string m_subURI;
	ConnectionMode m_mode;
	boost::asio::io_context m_io_context;
	tcp::socket m_socket;
	std::string m_lastError;

	bool CheckAddress(IpAddr address);
	bool CheckAddress(std::string address);
	bool CheckName(std::string server);
	bool CheckSubURI(std::string uri);
	IpAddr GatherAddress(std::string address);
};

