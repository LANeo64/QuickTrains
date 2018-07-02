#include "stdafx.h"
#include "Train.h"

int Train::s_id = 0;

Train::Train(std::string name, std::string designation, int cars, int length)
{
	m_id = s_id++;
	m_name = name;
	m_designation = designation;
	m_cars = cars;
	m_length = length;
}

Train::~Train()
{
}

int Train::GetID()
{
	return m_id;
}

std::string Train::GetName()
{
	return m_name;
}

std::string Train::GetDesignation()
{
	return m_designation;
}

int Train::GetLength()
{
	return m_length;
}

int Train::GetCarsNum()
{
	return m_cars;
}

std::string Train::GetOrigin()
{
	return m_origin;
}

bool Train::AddLocomotive(Locomotive * loco)
{
	bool exists = false;
	for (std::vector<Locomotive*>::iterator it = m_locomotives.begin(); it != m_locomotives.end(); it++) {
		if (loco->GetAddress() == (*it)->GetAddress()) {
			exists = true;
		}
	}
	if (exists) {
		return false;
	}
	else {
		m_locomotives.push_back(loco);
		return true;
	}
}

Locomotive * Train::GetLocomotive(int address)
{
	Locomotive* loco = NULL;
	for (std::vector<Locomotive*>::iterator it = m_locomotives.begin(); it != m_locomotives.end(); it++) {
		if (address == (*it)->GetAddress()) {
			loco = (*it);
		}
	}
	return loco;
}

std::vector<Locomotive*> Train::GetLocomotives()
{
	return m_locomotives;
}
