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

private:
	std::vector<Station*> m_stations;
	std::vector<RailPart*> m_parts;
	std::vector<Locomotive*> m_locomotives;
	std::vector<Train*> m_trains;
};

