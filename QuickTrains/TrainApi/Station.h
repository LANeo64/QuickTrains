#pragma once
class Station
{
public:
	Station();
	~Station();

private:
	std::string m_name;
	int m_id;
	int m_slots;
};

