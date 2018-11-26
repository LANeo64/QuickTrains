// TrainApi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "ApiManager.h"

int main()
{
	ApiManager& api = ApiManager::GetApi();
	api.SetServer("akela.mendelu.cz");
	api.SetServerPort(80);
	api.SetServerSubURI("/~xcizek/RKD");
	std::string d = api.GetLoks();
	std::cout << "Hello world!" << std::endl;
	std::cout << d << std::endl;
	std::getchar();
    return 0;
}

