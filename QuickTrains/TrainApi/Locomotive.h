#pragma once

#include <map>

#include "LocoState.h"

class Locomotive
{
public:
	enum LocoClass
	{
		STEAM,
		DIESEL,
		ENGINE,
		ELECTRO
	};

	Locomotive(std::string name, int address, LocoClass _class, std::string owner, std::string designation);
	~Locomotive();

	int GetAddress();

	void SetNote(std::string note);
	void SetFunction(LocoState::FunctionKey key, std::string);
	void SetState(LocoState* state);

private:
	std::string m_name;
	int m_address;
	std::string m_owner;
	std::string m_designation;
	std::string m_note;
	LocoClass m_class;
	std::map<LocoState::FunctionKey, std::string> m_functions;
	LocoState* m_state;
};

