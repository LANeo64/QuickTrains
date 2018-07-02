#pragma once

#include <vector>

#include "RailPart.h"
#include "RailPartState.h"
#include "MTB.h"

class PartSection :
	public RailPart
{
public:
	PartSection(std::string name, int id, std::string type);
	PartSection(std::string name, int id, std::string type, int length);
	PartSection(std::string name, int id, std::string type, std::string amplifier);
	PartSection(std::string name, int id, std::string type, int length, std::string amplifier);
	~PartSection();

	int GetLength();
	std::string GetAmplifier();
	bool IsOccupied();
	bool IsOccupied(int index);
	// and more information getting methods
	bool AddMTB(MTB* _mtb);
	void SetState(RailPartState* state);


private:
	int m_length;
	std::string m_amplifier;
	std::vector<MTB*> m_mtb;
	RailPartState* m_state;
};

