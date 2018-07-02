#include "stdafx.h"
#include "MTB.h"


MTB::MTB(int board, int port)
{
	m_board = (board > 0) ? board : 0;
	m_port = (port > 0) ? port : 0;
}

MTB::~MTB()
{
}

int MTB::GetPort()
{
	return m_port;
}

int MTB::GetBoard()
{
	return m_board;
}
