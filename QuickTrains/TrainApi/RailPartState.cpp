#include "stdafx.h"
#include "RailPartState.h"


RailPartState::RailPartState()
{
}


RailPartState::~RailPartState()
{
}

bool RailPartState::GetFlag(Flags flag)
{
	return m_flags[flag];
}

void RailPartState::SetFlag(Flags flag, bool state)
{
	m_flags[flag] = state;
}

bool RailPartState::GetDivisionState(int key)
{
	return m_divisionState[key];
}

void RailPartState::SetDivisionState(int key, bool state)
{
	m_divisionState[key] = state;
}

int RailPartState::GetNumTrains()
{
	return m_trains.size();
}

Train * RailPartState::GetTrain(std::string name)
{
	Train* t = NULL;
	for (std::vector<Train*>::iterator it = m_trains.begin(); it != m_trains.end(); it++) {
		if (name.compare((*it)->GetName())) {
			t = (*it);
		}
	}
	return t;
}

Train * RailPartState::GetTrain(int id)
{
	Train* t = NULL;
	for (std::vector<Train*>::iterator it = m_trains.begin(); it != m_trains.end(); it++) {
		if (id == (*it)->GetID()) {
			t = (*it);
		}
	}
	return t;
}

Train * RailPartState::GetTrainAt(int index)
{
	try {
		Train* t = m_trains.at(index);
		return t;
	}
	catch (const std::out_of_range& oor) {
		return NULL;
	}
}

bool RailPartState::AddTrain(Train * _train)
{
	if (this->TrainExists(_train->GetDesignation())) {
		return false;
	}
	else {
		m_trains.push_back(_train);
		return true;
	}
}

bool RailPartState::RemoveTrain(Train * _train)
{
	if (this->TrainExists(_train->GetDesignation())) {
		int i = -1;
		Train* t;
		do {
			i++;
			t = m_trains.at(i);
		} while (t->GetDesignation().compare(_train->GetDesignation()));
		m_trains.erase(m_trains.begin() + i);
		return true;
	}
	else {
		return false;
	}
}

bool RailPartState::TrainExists(std::string designation)
{
	bool exists = false;
	for (std::vector<Train*>::iterator it = m_trains.begin(); it != m_trains.end(); it++) {
		if (designation.compare((*it)->GetDesignation())) {
			exists = true;
		}
	}
	return exists;
}
