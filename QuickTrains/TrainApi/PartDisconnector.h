#pragma once
#include "RailPart.h"
class PartDisconnector :
	public RailPart
{
public:
	PartDisconnector(std::string name, int id, std::string type);
	~PartDisconnector();
};

