#pragma once
#include "RailPart.h"
class PartHitch :
	public RailPart
{
public:
	PartHitch(std::string name, int id, std::string type);
	~PartHitch();
};

