#include "stdafx.h"
#include "Locomotive.h"


Locomotive::Locomotive(std::string name, int address, LocoClass _class, std::string owner, std::string designation)
{
	m_name = name;
	m_address = address;
	m_class = _class;
	m_owner = owner;
	m_designation = designation;
	m_note = "";
}

Locomotive::~Locomotive()
{
	if (m_state != NULL) {
		delete m_state;
	}
}

int Locomotive::GetAddress()
{
	return m_address;
}
