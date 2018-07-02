#pragma once

#include <map>

class LocoState
{
public:
	enum FunctionKey
	{
		F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,F13
	};

	struct Tacho {
		double meters;
		int blocks;
	};

	LocoState(std::string station, bool dir, Tacho fwd, Tacho bwd);
	~LocoState();

	void SetFunction(FunctionKey key, bool value);
	bool Getfunction(FunctionKey key);
	bool GetDirection();
	void SetSpeed(int speed);
	Tacho GetPathForward();
	Tacho GetPathBackward();


private:
	int m_speedDEG;
	int m_speedKPH;
	bool m_direction;
	std::map<FunctionKey, bool> m_functions;
	std::string m_station;
	Tacho m_forward;
	Tacho m_backward;
};

