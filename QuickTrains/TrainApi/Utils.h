#pragma once

#include <vector>
#include <sstream>

class Utils
{
public:
	static std::vector<std::string> Explode(std::string s, char delim) {
		std::vector<std::string> result;
		std::istringstream iss(s);

		for (std::string token; std::getline(iss, token, delim); )
		{
			result.push_back(std::move(token));
		}

		return result;
	}

	static int ToInt(std::string s) {
		int num;
		std::istringstream(s) >> num;
		return num;
	}

private:
	Utils() {}
	~Utils() {}
};
