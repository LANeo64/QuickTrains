#include "stdafx.h"
#include "HttpClient.h"


HttpClient::HttpClient()
{
}


HttpClient::~HttpClient()
{
}

bool HttpClient::SetAddress(IpAddr address)
{
	if (CheckAddress(address)) {
		m_serverAddress = address;
		return true;
	}
	else {
		return false;
	}
}

bool HttpClient::SetAddress(std::string address)
{
	IpAddr add = GatherAddress(address);
	return SetAddress(add);
}

bool HttpClient::SetPort(int port)
{
	if (port > 0) {
		m_port = port;
		return true;
	}
	else {
		return false;
	}
}

bool HttpClient::CheckAddress(IpAddr address)
{
	if (
		(address.A < 256) &&
		(address.B < 256) &&
		(address.C < 256) &&
		(address.D < 256) &&
		(address.A > 0)
		) {
		bool good = true;
		switch (address.A) {
		case 10:
			if ((address.B == 0) && (address.C == 0) && (address.D == 0)) {
				good = false;
			}
			break;
		case 127:
			if ((address.B == 0) && (address.C == 0) && (address.D == 0)) {
				good = false;
			}
			break;
		case 192:
			if ((address.B != 168) || ((address.C == 0) && (address.D == 0))) {
				good = false;
			}
			break;
		}
		
		return good;
	}
	else {
		return false;
	}
}

HttpClient::IpAddr HttpClient::GatherAddress(std::string address)
{
	HttpClient::IpAddr add;
	std::vector<std::string> ip = Utils::Explode(address, '.');
	if (ip.size() == 4) {
		add.A = Utils::ToInt(ip.at(0));
		add.B = Utils::ToInt(ip.at(1));
		add.C = Utils::ToInt(ip.at(2));
		add.D = Utils::ToInt(ip.at(3));
	}
	else {
		add.A = 127;
		add.B = 0;
		add.C = 0;
		add.D = 1;
	}
	return add;
}
