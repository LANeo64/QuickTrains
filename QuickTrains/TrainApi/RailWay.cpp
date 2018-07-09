#include "stdafx.h"
#include "RailWay.h"


int RailWay::s_id = 0;

RailWay::RailWay()
{
	m_id = s_id++;
	std::ostringstream s;
	s << "Railway ";
	s << m_id;
	m_name = s.str();
}

RailWay::RailWay(std::string name)
{
	m_id = s_id++;
	m_name = name;
}

RailWay::RailWay(int id, std::string name)
{
	if (id > s_id) {
		m_id = id;
	}
	else {
		m_id = s_id++;
	}
	m_name = name;
}


RailWay::~RailWay()
{
	for (std::vector<Station*>::iterator it = m_stations.begin(); it != m_stations.end(); it++) {
		delete (*it);
	}
	m_stations.clear();

	for (std::vector<RailPart*>::iterator it = m_parts.begin(); it != m_parts.end(); it++) {
		delete (*it);
	}
	m_parts.clear();

	for (std::vector<Locomotive*>::iterator it = m_locomotives.begin(); it != m_locomotives.end(); it++) {
		delete (*it);
	}
	m_locomotives.clear();

	for (std::vector<Train*>::iterator it = m_trains.begin(); it != m_trains.end(); it++) {
		delete (*it);
	}
	m_trains.clear();
}

bool RailWay::AddStation(Station * st)
{
	bool exists = false;
	for (std::vector<Station*>::iterator it = m_stations.begin(); it != m_stations.end(); it++) {
		if (((*it)->GetName().compare(st->GetName()) == 0) || ((*it)->GetID() == st->GetID())) {
			exists = true;
		}
	}
	if (exists) {
		return false;
	}
	else {
		m_stations.push_back(st);
		return true;
	}
}

bool RailWay::AddRailPart(RailPart * part)
{
	bool exists = false;
	for (std::vector<RailPart*>::iterator it = m_parts.begin(); it != m_parts.end(); it++) {
		if ((*it)->GetID() == part->GetID()) {
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

bool RailWay::AddLocomotive(Locomotive * loco)
{
	bool exists = false;
	for (std::vector<Locomotive*>::iterator it = m_locomotives.begin(); it != m_locomotives.end(); it++) {
		if ((*it)->GetAddress() == loco->GetAddress()) {
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

bool RailWay::AddTrain(Train * tr)
{
	bool exists = false;
	for (std::vector<Train*>::iterator it = m_trains.begin(); it != m_trains.end(); it++) {
		if (((*it)->GetID() == tr->GetID()) || ((*it)->GetDesignation().compare(tr->GetDesignation()))) {
			exists = true;
		}
	}
	if (exists) {
		return false;
	}
	else {
		m_trains.push_back(tr);
		return true;
	}
}
