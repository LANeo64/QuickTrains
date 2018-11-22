// TrainApi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "ApiManager.h"

int main()
{
	ApiManager& api = ApiManager::GetApi();
	api.SetServerIP("192.168.1.1");
	api.SetServerPort(8006);
	api.SetServerSubURI("edsa-TrainServer");
	std::cout << "Hello world!" << std::endl;
	std::getchar();
    return 0;
}

