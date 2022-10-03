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
	std::string GetArgument() { return m_argument; }

private:
	std::string RemoveLeadingDashes(std::string s);

	std::map<std::string, std::string> m_options;
	std::string m_argument = "";
};

