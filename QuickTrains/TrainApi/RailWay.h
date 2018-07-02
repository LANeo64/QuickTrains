#pragma once

#include <vector>

#include "Station.h"
#include "RailPart.h"
#include "Locomotive.h"
#include "Train.h"

class RailWay
{
public:
	RailWay();
	~RailWay();

	bool AddStation(Station* st);
	bool AddRailPart(RailPart* part);
	bool AddLocomotive(Locomotive* loco);
	bool AddTrain(Train* tr);

private:
	std::vector<Station*> m_stations;
	std::vector<RailPart*> m_parts;
	std::vector<Locomotive*> m_locomotives;
	std::vector<Train*> m_trains;
};

