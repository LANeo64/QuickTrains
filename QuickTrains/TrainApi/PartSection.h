#pragma once
#include "RailPart.h"
class PartSection :
	public RailPart
{
public:
	PartSection(std::string name, int id, std::string type);
	~PartSection();
};

