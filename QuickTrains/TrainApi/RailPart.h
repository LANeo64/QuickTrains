#pragma once

#include "RailPartType.h"

class RailPart
{
public:
	RailPart(std::string name, int id, RailPartType type);
	RailPart(std::string name, int id, std::string type);
	~RailPart();

	std::string GetName();
	int GetID();
	RailPartType GetType();
	std::string GetTypeString();

protected:
	static int s_baseID;

	std::string m_name;
	int m_id;
	RailPartType m_type;

private:
	RailPartType GetRailType(std::string type);
};

