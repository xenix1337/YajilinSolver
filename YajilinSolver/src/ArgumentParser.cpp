#include "ArgumentParser.h"

#include <algorithm>

ArgumentParser::ArgumentParser(int argc, char** argv)
{
	for (int i = 1; i < argc; i++) {
		std::string argString(argv[i]);
		argString = RemoveLeadingDashes(argString);

		// Lookup the next argument
		if (i != argc - 1 && argv[i + 1][0] != '-') {
			// Next argument is value to this argument
			std::string paramString(argv[i + 1]);

			m_bools[argString] = true; // TODO: Parse properly
			m_strings[argString] = paramString;
			if (!paramString.empty() && paramString.find_first_not_of("0123456789") == std::string::npos) {
				m_ints[argString] = atoi(paramString.c_str());
			}

			i++; // Skip the next argument (value to this)
		}
		else {
			m_bools[argString] = true;
		}
	}
}

bool ArgumentParser::GetBool(std::string key, bool defaultValue)
{
	if (m_bools.find(key) != m_bools.end()) return m_bools[key];
	return defaultValue;
}

int32_t ArgumentParser::GetInt(std::string key, int defaultValue)
{
	if (m_ints.find(key) != m_ints.end()) return m_ints[key];
	return defaultValue;
}

std::string ArgumentParser::GetString(std::string key, std::string defaultValue)
{
	if (m_strings.find(key) != m_strings.end()) return m_strings[key];
	return defaultValue;
}

std::string ArgumentParser::RemoveLeadingDashes(std::string s)
{
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != '-') return s.substr(i);
	}
	return "";
}
