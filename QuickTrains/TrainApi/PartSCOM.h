#pragma once
#include "RailPart.h"
class PartSCOM :
	public RailPart
{
public:
	PartSCOM(std::string name, int id, std::string type);
	~PartSCOM();
};

