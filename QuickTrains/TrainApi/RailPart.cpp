#include "stdafx.h"
#include "RailPart.h"

int RailPart::s_baseID = 1000;

RailPart::RailPart(std::string name, int id, RailPartType type)
{
	m_name = name;
	m_id = (id > 0) ? id : s_baseID++;
	m_type = type;
}

RailPart::RailPart(std::string name, int id, std::string type)
{
	m_name = name;
	m_id = (id > 0) ? id : s_baseID++;
	m_type = GetRailType(type);
}

RailPart::~RailPart()
{
}

std::string RailPart::GetName()
{
	return m_name;
}

int RailPart::GetID()
{
	return m_id;
}

RailPartType RailPart::GetType()
{
	return m_type;
}

std::string RailPart::GetTypeString()
{
	std::string type = "";
	switch (m_type) {
	case TYPE_SWITCH:
		type = "vyhybka";
		break;
	case TYPE_HITCH:
		type = "uvazka";
		break;
	case TYPE_IR:
		type = "ir";
		break;
	case TYPE_SECTION:
		type = "usek";
		break;
	case TYPE_TRACK_SECTION:
		type = "tratUsek";
		break;
	case TYPE_SCOM:
		type = "scom";
		break;
	case TYPE_LOCK:
		type = "zamek";
		break;
	case TYPE_TRACK:
		type = "trat";
		break;
	case TYPE_DISCONNECT:
		type = "rozpojovac";
		break;
	}
	return type;
}

RailPartType RailPart::GetRailType(std::string type)
{
	RailPartType partType;
	if (type.compare("vyhybka") == 0) {
		partType = RailPartType::TYPE_SWITCH;
	}
	else if (type.compare("usek") == 0) {
		partType = RailPartType::TYPE_SECTION;
	}
	else if (type.compare("tratUsek") == 0) {
		partType = RailPartType::TYPE_TRACK_SECTION;
	}
	else if (type.compare("scom") == 0) {
		partType = RailPartType::TYPE_SCOM;
	}
	else if (type.compare("zamek") == 0) {
		partType = RailPartType::TYPE_LOCK;
	}
	else if (type.compare("ir") == 0) {
		partType = RailPartType::TYPE_IR;
	}
	else if (type.compare("rozpojovac") == 0) {
		partType = RailPartType::TYPE_DISCONNECT;
	}
	else if (type.compare("trat") == 0) {
		partType = RailPartType::TYPE_TRACK;
	}
	else if (type.compare("uvazka") == 0) {
		partType = RailPartType::TYPE_HITCH;
	}
	return partType;
}
