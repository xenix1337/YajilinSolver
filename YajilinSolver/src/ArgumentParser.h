#pragma once

#include <vector>
#include <string>
#include <map>

class ArgumentParser
{
public:
	ArgumentParser(int argc, char** argv);

	bool GetBool(std::string key, bool defaultValue = false);
	int32_t GetInt(std::string key, int defaultValue = 0);
	std::string GetString(std::string key, std::string defaultValue = "");

private:
	std::string RemoveLeadingDashes(std::string s);

	std::vector<std::string> m_flags;
	std::map<std::string, bool> m_bools;
	std::map<std::string, int32_t> m_ints;
	std::map<std::string, std::string> m_strings;
};

