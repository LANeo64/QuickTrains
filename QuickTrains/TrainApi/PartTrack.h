#pragma once
#include "RailPart.h"
class PartTrack :
	public RailPart
{
public:
	PartTrack(std::string name, int id, std::string type);
	~PartTrack();
};

