#pragma once
#include "RailPart.h"
class PartLock :
	public RailPart
{
public:
	PartLock(std::string name, int id, std::string type);
	~PartLock();
};

