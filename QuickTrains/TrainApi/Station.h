#pragma once

#include <vector>
#include <map>

#include "Platform.h"
#include "Train.h"

class Station
{
public:
	Station();
	~Station();

	std::string GetName();
	int GetID();

private:
	std::string m_name;
	int m_id;
	int m_sideTracks;
	std::vector<Platform*> m_platforms;
	std::vector<Train*> m_Trains;
	std::vector<Station*> m_neighbors;
};

