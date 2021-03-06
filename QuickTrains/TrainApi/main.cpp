// TrainApi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "ApiManager.h"

int main()
{
	ApiManager& api = ApiManager::GetApi();
	api.SetServer("83.240.108.164");
	api.SetServerPort(80);
	api.SetServerSubURI("/LANeo/RKD");

	std::vector<Locomotive*> locomotives = api.GetLoks();
	//api.TestIt();

	for (std::vector<Locomotive*>::iterator it = locomotives.begin(); it != locomotives.end(); it++) {
		std::cout << (*it)->GetAddress() << std::endl;
	}
	std::cout << "krteček" << std::endl;
	std::getchar();
    return 0;
}

