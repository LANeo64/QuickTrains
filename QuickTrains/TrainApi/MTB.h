#pragma once
class MTB
{
public:
	MTB(int board, int port);
	~MTB();

private:
	int m_board;
	int m_port;
};

