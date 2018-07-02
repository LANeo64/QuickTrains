#include "stdafx.h"
#include "Station.h"


Station::Station()
{
}


Station::~Station()
{
}

std::string Station::GetName()
{
	return m_name;
}

int Station::GetID()
{
	return m_id;
}
