#pragma once

#include <vector>
#include <sstream>

#include "Station.h"
#include "RailPart.h"
#include "Locomotive.h"
#include "Train.h"

class RailWay
{
public:
	RailWay();
	RailWay(std::string name);
	RailWay(int id, std::string name);
	~RailWay();

	bool AddStation(Station* st);
	bool AddRailPart(RailPart* part);
	bool AddLocomotive(Locomotive* loco);
	bool AddTrain(Train* tr);

private:
	static int s_id;

	int m_id;
	std::string m_name;
	std::vector<Station*> m_stations;
	std::vector<RailPart*> m_parts;
	std::vector<Locomotive*> m_locomotives;
	std::vector<Train*> m_trains;
};

