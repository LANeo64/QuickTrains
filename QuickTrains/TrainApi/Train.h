#pragma once

#include <vector>

#include "Locomotive.h"

class Train
{
public:
	enum TrainType
	{
		PASSENGER, FREIGHT
	};
	Train(std::string name, std::string designation, int cars, int length);
	~Train();

	int GetID();
	std::string GetName();
	std::string GetDesignation();
	int GetLength();
	int GetCarsNum();
	std::string GetOrigin();
	bool AddLocomotive(Locomotive* loco);
	Locomotive* GetLocomotive(int address);
	std::vector<Locomotive*> GetLocomotives();


private:
	static int s_id;

	int m_id;
	std::string m_name;
	std::string m_designation;
	std::vector<Locomotive*> m_locomotives;
	int m_length;
	int m_cars;
	std::string m_origin;
};

