#include "ArgumentParser.h"

#include <algorithm>

ArgumentParser::ArgumentParser(int argc, char** argv)
{
	for (int i = 1; i < argc; i++) {
		std::string argString(argv[i]);
		if (argString[0] != '-') {
			m_argument = argString;
			continue;
		}

		argString = RemoveLeadingDashes(argString);
		size_t equalSignPos = argString.find('=');

		if (equalSignPos == std::string::npos) 
			m_options.insert({ argString, std::string("1")});
		else
			m_options.insert({ argString.substr(0, equalSignPos), argString.substr(equalSignPos + 1) });
	}
}

bool ArgumentParser::GetBool(std::string key, bool defaultValue)
{
	if (m_options.find(key) == m_options.end()) return defaultValue;

	if (atoi(m_options[key].c_str()) == 1 || m_options[key] == "TRUE" || m_options[key] == "true") return true;
	return false;
}

int32_t ArgumentParser::GetInt(std::string key, int defaultValue)
{
	if (m_options.find(key) == m_options.end()) return defaultValue;
	return atoi(m_options[key].c_str());
}

std::string ArgumentParser::GetString(std::string key, std::string defaultValue)
{
	if (m_options.find(key) == m_options.end()) return defaultValue;
	return m_options[key];
}

std::string ArgumentParser::RemoveLeadingDashes(std::string s)
{
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != '-') return s.substr(i);
	}
	return "";
}
