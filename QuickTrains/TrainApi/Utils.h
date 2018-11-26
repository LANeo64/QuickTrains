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

	static std::string Concat(std::string s1, std::string s2) {
		std::ostringstream os;
		os << s1 << s2;
		return os.str();
	}

	static std::string Concat(std::string s, int num) {
		std::ostringstream os;
		os << s << num;
		return os.str();
	}

private:
	Utils() {}
	~Utils() {}
};
