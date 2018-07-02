#include "stdafx.h"
#include "Platform.h"

int Platform::s_id = 0;

Platform::Platform(int number, PlatformType type)
{
	m_id = s_id++;
	m_number = number;
	m_type = type;
	m_length = 0;
	std::ostringstream s;
	s << number;
	m_name = s.str();
}

Platform::Platform(int number, PlatformType type, int length)
{
	m_id = s_id++;
	m_number = number;
	m_type = type;
	m_length = length;
	std::ostringstream s;
	s << number;
	m_name = s.str();
}

Platform::Platform(int number, PlatformType type, std::string name)
{
	m_id = s_id++;
	m_number = number;
	m_type = type;
	m_length = 0;
	m_name = name;
}

Platform::Platform(int number, PlatformType type, int length, std::string name)
{
	m_id = s_id++;
	m_number = number;
	m_type = type;
	m_length = length;
	m_name = name;
}

Platform::~Platform()
{
}

bool Platform::AddRailPart(RailPart * part)
{
	bool exists = false;
	for (std::vector<RailPart*>::iterator it = m_parts.begin(); it != m_parts.end(); it++) {
		if (part->GetID() == (*it)->GetID()) {
			exists = true;
		}
	}

	if (exists) {
		return false;
	}
	else {
		m_parts.push_back(part);
		return true;
	}
}

std::vector<RailPart*> Platform::GetParts()
{
	return m_parts;
}

std::vector<RailPart*> Platform::GetParts(RailPart::RailPartType type)
{
	std::vector<RailPart*> parts;
	for (std::vector<RailPart*>::iterator it = m_parts.begin(); it != m_parts.end(); it++) {
		if ((*it)->GetType() == type) {
			parts.push_back((*it));
		}
	}

	return parts;
}

RailPart * Platform::GetPart(int id)
{
	RailPart* part = NULL;
	for (std::vector<RailPart*>::iterator it = m_parts.begin(); it != m_parts.end(); it++) {
		if ((*it)->GetID() == id) {
			part = (*it);
		}
	}
	return part;
}

RailPart * Platform::GetPart(std::string name)
{
	RailPart* part = NULL;
	for (std::vector<RailPart*>::iterator it = m_parts.begin(); it != m_parts.end(); it++) {
		if ((*it)->GetName().compare(name) == 0) {
			part = (*it);
		}
	}
	return part;
}
