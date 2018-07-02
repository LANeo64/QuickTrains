#pragma once

#include "RailPartType.h"

class RailPart
{
public:
	enum RailPartType {
		TYPE_SWITCH,
		TYPE_SECTION,
		TYPE_TRACK,
		TYPE_TRACK_SECTION,
		TYPE_SCOM,
		TYPE_LOCK,
		TYPE_IR,
		TYPE_DISCONNECT,
		TYPE_HITCH
	};

	RailPart(std::string name, int id, RailPartType type);
	RailPart(std::string name, int id, std::string type);
	~RailPart();

	std::string GetName();
	int GetID();
	RailPartType GetType();
	std::string GetTypeString();

protected:
	static int s_baseID;

	std::string m_name;
	int m_id;
	RailPartType m_type;

private:
	RailPartType GetRailType(std::string type);
};

/*
class A{
public:
A(int alfa, int beta){
m_alfa = alfa;
m_beta = beta;
}

int GetAlfa(){
return m_alfa;
}
int GetBeta(){
return m_beta;
}

private:
int m_alfa;
int m_beta;
};

class B: public A{
public:
B(int alfa, int beta, int gama):A(alfa,beta){
m_gama = gama;
}

int GetGama(){
return m_gama;
}

private:
int m_gama;
};



int main() {
A* mojeA = new A(1,2);
cout<<"Alfa: " << mojeA->GetAlfa() << endl;
cout<<"Beta: " << mojeA->GetBeta() << endl;

B* mojeB = new B(4,5,6);
cout<<"Alfa: " << mojeB->GetAlfa() << endl;
cout<<"Beta: " << mojeB->GetBeta() << endl;
cout<<"Gama: " << mojeB->GetGama() << endl;

A* mojeC = new B(10,20,30);
cout<<"Alfa: " << mojeC->GetAlfa() << endl;
cout<<"Beta: " << mojeC->GetBeta() << endl;
cout<<"Gama: " << ((B*)mojeC)->GetGama() << endl;

}
*/
