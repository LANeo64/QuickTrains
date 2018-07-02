#pragma once

#include <vector>
#include <map>

#include "Train.h"

class RailPartState
{
public:
	enum Flags
	{
		OCCUPATION,
		POWER_SUPPLY,
		SHORT_CIRCUIT,
		DCC
	};

	RailPartState();
	~RailPartState();
	
	bool GetFlag(Flags flag);
	void SetFlag(Flags flag, bool state);
	bool GetDivisionState(int key);
	void SetDivisionState(int key, bool state);
	int GetNumTrains();
	Train* GetTrain(std::string name);
	Train* GetTrain(int id);
	Train* GetTrainAt(int index);
	bool AddTrain(Train* _train);
	bool RemoveTrain(Train* _train);

private:
	std::map<Flags, bool> m_flags;
	std::map<int, bool> m_divisionState;
	std::vector<Train*> m_trains;

	bool TrainExists(std::string designation);
};

