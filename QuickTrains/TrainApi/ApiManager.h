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

	// Client configuration methods
	void SetServerIP(std::string ip);
	void SetServerIP(HttpClient::IpAddr ip);
	void SetServerPort(unsigned int port);
	void SetServerSubURI(std::string uri);

	// Train control methods
	std::vector<Locomotive*> GetLocomotives();
	std::vector<Train*> GetTrains();

	// Rail control methods
	std::vector<Station*> GetStations();
	std::vector<RailPart*> GetRailParts();
	std::vector<RailPart*> GetRailParts(RailPart::RailPartType type);
	std::vector<RailPart*> GetRailParts(Station* A);
	std::vector<RailPart*> GetRailParts(Station* A, Station* B);
	std::vector<RailPart*> GetRailParts(RailPart* A, RailPart* B);

	// Station control methods

private:
	ApiManager();
	~ApiManager();

	// server <---> client communication methods
	std::string ServerGet(HttpClient::Command com);
	std::string ServerGet(HttpClient::Command com, int id);
	bool ServerPut(HttpClient::Command com, std::string payload);
	bool ServerPut(HttpClient::Command com, int id, std::string payload);

	RailWay* m_railWay;
	HttpClient* m_http;
};
