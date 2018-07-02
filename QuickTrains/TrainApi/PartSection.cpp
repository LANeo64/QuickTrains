#include "stdafx.h"
#include "PartSection.h"


PartSection::PartSection(std::string name, int id, std::string type) : RailPart(name, id, type)
{
	m_length = 0;
	m_amplifier = "";
	m_state = NULL;
}

PartSection::PartSection(std::string name, int id, std::string type, int length) : RailPart(name, id, type)
{
	m_length = length;
	m_amplifier = "";
	m_state = NULL;
}

PartSection::PartSection(std::string name, int id, std::string type, std::string amplifier) : RailPart(name, id, type)
{
	m_length = 0;
	m_amplifier = amplifier;
	m_state = NULL;
}


PartSection::PartSection(std::string name, int id, std::string type, int length, std::string amplifier) : RailPart(name, id, type)
{
	m_length = length;
	m_amplifier = amplifier;
	m_state = NULL;
}

PartSection::~PartSection()
{
	for (std::vector<MTB*>::iterator it = m_mtb.begin(); it != m_mtb.end(); it++) {
		delete (*it);
	}
	if (m_state != NULL) {
		delete m_state;
	}
}

int PartSection::GetLength()
{
	return m_length;
}

std::string PartSection::GetAmplifier()
{
	return m_amplifier;
}

bool PartSection::IsOccupied()
{
	if (m_state != NULL) {
		return m_state->GetFlag(RailPartState::OCCUPATION);
	}
	else {
		return false;
	}
}

bool PartSection::IsOccupied(int index)
{
	if (m_state != NULL) {
		return m_state->GetDivisionState(index);
	}
	else {
		return false;
	}
}

bool PartSection::AddMTB(MTB * _mtb)
{
	bool exists = false;
	for (std::vector<MTB*>::iterator it = m_mtb.begin(); it != m_mtb.end(); it++) {
		if ((_mtb->GetBoard() == (*it)->GetBoard()) && (_mtb->GetPort() == (*it)->GetPort())) {
			exists = true;
		}		
	}
	if (exists) {
		return false;
	}
	else {
		m_mtb.push_back(_mtb);
		return true;
	}
}

void PartSection::SetState(RailPartState * state)
{
	m_state = state;
}
