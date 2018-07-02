#pragma once

#include <vector>
#include <sstream>

#include "RailPart.h"

class Platform
{
public:
	enum PlatformType {
		FREIGHT, PASSENGER
	};

	Platform(int number, PlatformType type);
	Platform(int number, PlatformType type, int length);
	Platform(int number, PlatformType type, std::string name);
	Platform(int number, PlatformType type, int length, std::string name);
	~Platform();

	bool AddRailPart(RailPart* part);
	std::vector<RailPart*> GetParts();
	std::vector<RailPart*> GetParts(RailPart::RailPartType type);
	RailPart* GetPart(int id);
	RailPart* GetPart(std::string name);

private:
	static int s_id;

	int m_id;
	int m_number;
	std::string m_name;
	int m_length;
	PlatformType m_type;
	std::vector<RailPart*> m_parts;
};

