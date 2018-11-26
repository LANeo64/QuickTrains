#pragma once

#include <stdexcept>

#include "RailWay.h"
#include "HttpClient.h"

class ApiManager
{
public:
	static ApiManager& GetApi() {
		static ApiManager s;
		return s;
	}

	// Client configuration methods
	void SetServer(std::string server);
	void SetServerPort(unsigned int port);
	void SetServerSubURI(std::string uri);
	void SetHotApi(bool state);
	void KRT() { 
		m_http->Connect();
		std::string data = m_http->GetData(HttpClient::Request(HttpClient::BLOKY));
		std::cout << data;
	}

	// Train control methods
	std::vector<Locomotive*> GetLocomotives();
	std::vector<Train*> GetTrains();
	std::vector<Train*> GetTrains(Station* A);
	Train* GetTrain(int id);
	Train* GetTrain(std::string name);
	Locomotive* GetLocomotive(int address);
	Locomotive* GetLocomotive(std::string name);

	// Rail control methods
	std::vector<RailPart*> GetRailParts();								// Gets the list of all Railparts
	std::vector<RailPart*> GetRailParts(RailPart::RailPartType type);	// Gets the list of all Railparts of certain type
	std::vector<RailPart*> GetRailParts(Station* A);					// Gets the list of all Railparts of a certain Station
	std::vector<RailPart*> GetRailParts(Station* A, Station* B);		// Gets the list of all Railparts between two Stations
	std::vector<RailPart*> GetRailParts(RailPart* A, RailPart* B);		// Gets the list of all Railparts between another two Railparts
	void SetSwitch(int id, bool position);

	// Station control methods
	std::vector<Station*> GetStations();								// Gets the list of Stations

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
	bool m_apiHotMode;
};
