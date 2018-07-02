#pragma once
class MTB
{
public:
	MTB(int board, int port);
	~MTB();

	int GetPort();
	int GetBoard();

private:
	int m_board;
	int m_port;
};

