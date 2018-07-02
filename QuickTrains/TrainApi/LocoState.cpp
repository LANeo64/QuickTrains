#include "stdafx.h"
#include "LocoState.h"


LocoState::LocoState(std::string station, bool dir, Tacho fwd, Tacho bwd)
{
	m_speedDEG = 0;
	m_speedKPH = 0;
	m_station = station;
	m_direction = dir;
	m_forward = fwd;
	m_backward = bwd;
}

LocoState::~LocoState()
{
}

void LocoState::SetFunction(FunctionKey key, bool value)
{
	m_functions[key] = value;
}

bool LocoState::Getfunction(FunctionKey key)
{
	return m_functions[key];
}

bool LocoState::GetDirection()
{
	return m_direction;
}

void LocoState::SetSpeed(int speed)
{
	m_speedDEG = speed;
}

LocoState::Tacho LocoState::GetPathForward()
{
	return m_forward;
}

LocoState::Tacho LocoState::GetPathBackward()
{
	return m_backward;
}
