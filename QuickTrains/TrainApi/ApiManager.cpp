#include "stdafx.h"
#include "ApiManager.h"


void ApiManager::SetServer(std::string server)
{
	if (!m_http->SetHost(server)) {
		throw std::invalid_argument("Invalid server IP or hostname");
	}
}

void ApiManager::SetServerPort(unsigned int port)
{
	if (!m_http->SetPort(port)) {
		throw std::invalid_argument("Invalid server socket Port");
	}
}

void ApiManager::SetServerSubURI(std::string uri)
{
	if (!m_http->SetSubURI(uri)) {
		throw std::invalid_argument("Invalid subURI string");
	}
}

void ApiManager::SetHotApi(bool state)
{
	m_apiHotMode = state;
}

ApiManager::ApiManager()
{
	m_railWay = new RailWay();
	m_http = new HttpClient();
	m_apiHotMode = true;
}


ApiManager::~ApiManager()
{
	delete m_railWay;
	delete m_http;
}

std::string ApiManager::ServerGet(HttpClient::Command com)
{
	return m_http->GetData(HttpClient::Request(com));
}

std::string ApiManager::ServerGet(HttpClient::Command com, int id)
{
	return m_http->GetData(HttpClient::Request(com, id));
}

bool ApiManager::ServerPut(HttpClient::Command com, std::string payload)
{
	return m_http->SetData(HttpClient::Request(com),payload);
}

bool ApiManager::ServerPut(HttpClient::Command com, int id, std::string payload)
{
	return m_http->SetData(HttpClient::Request(com,id), payload);
}

std::vector<Locomotive*> ApiManager::GetLoks()
{
	std::string s;
	rapidjson::Document document;
	std::vector<Locomotive*> locomotives;
	Locomotive* loco;
	try
	{
		s = m_http->GetData(HttpClient::Request(HttpClient::LOKS));
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception:\n" << e.what() << "\n";
	}
	document.Parse(s.c_str());
	if (document.IsObject()) {
		if (document.HasMember("loks") && document["loks"].IsArray()) {
			const rapidjson::Value& loks = document["loks"];
			for (rapidjson::SizeType i = 0; i < loks.Size(); i++) { // Uses SizeType instead of size_t
				loco = new Locomotive(
					loks[i]["nazev"].GetString(),
					loks[i]["adresa"].GetInt(),
					Locomotive::GetClass(loks[i]["trida"].GetString()),
					loks[i]["majitel"].GetString(),
					loks[i]["oznaceni"].GetString()
				);
				if (loks[i].HasMember("poznamka")) {
					loco->SetNote(loks[i]["poznamka"].GetString());
				}
				if (loks[i].HasMember("vyznamFunkci")) {
					const rapidjson::Value& fce = loks[i]["vyznamFunkci"];
					for (rapidjson::SizeType j = 0; (j < fce.Size()) && (j <= LocoState::F13); j++) {
						loco->SetFunction((LocoState::FunctionKey)j, fce[j].GetString());
					}
				}
				locomotives.push_back(loco);
			}
		}
	}
	else {
		throw std::runtime_error("Returned JSON is not an object");
	}

	return locomotives;
}

void ApiManager::TestIt()
{
	try
	{
		m_http->Test();
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception:\n" << e.what() << "\n";
	}
}
