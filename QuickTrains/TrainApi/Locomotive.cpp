#include "stdafx.h"
#include "Locomotive.h"


Locomotive::LocoClass Locomotive::GetClass(std::string str)
{
	boost::algorithm::to_lower(str);
	if (str.compare("diesel")) return LocoClass::DIESEL;
	if (str.compare("parni")) return LocoClass::STEAM;
	if (str.compare("motor")) return LocoClass::ENGINE;
	if (str.compare("elektrika")) return LocoClass::ELECTRO;

	return LocoClass::ENGINE;
}

Locomotive::Locomotive(std::string name, int address, LocoClass _class, std::string owner, std::string designation)
{
	m_name = name;
	m_address = address;
	m_class = _class;
	m_owner = owner;
	m_designation = designation;
	m_note = "";
	m_state = NULL;
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

void Locomotive::SetNote(std::string note)
{
	m_note = note;
}

void Locomotive::SetFunction(LocoState::FunctionKey key, std::string s)
{
	m_functions[key] = s;
}
