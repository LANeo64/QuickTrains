#pragma once
#include "PartSection.h"
class PartTrackSection :
	public PartSection
{
public:
	PartTrackSection(std::string name, int id, std::string type);
	~PartTrackSection();
};

