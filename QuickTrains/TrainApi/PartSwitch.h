#pragma once
#include "RailPart.h"
class PartSwitch :
	public RailPart
{
public:
	PartSwitch(std::string name, int id, std::string type);
	~PartSwitch();
};

