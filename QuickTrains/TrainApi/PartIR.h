#pragma once
#include "RailPart.h"
class PartIR :
	public RailPart
{
public:
	PartIR(std::string name, int id, std::string type);
	~PartIR();
};

