#pragma once
#include "windows.h"
#include <vector>
#include <string>

namespace Lippets
{
	namespace Strings
	{
		bool replace(std::string &str, const std::string_view &from, const std::string_view &to);
		std::vector<std::string>::const_iterator get_max_length_string(const std::vector<std::string> &lines);
		std::vector<std::string>::const_iterator get_max_length_string(const std::vector<std::vector<std::string>> &lines);
		bool isDigit(const std::string_view &str);
		bool strstr(const std::string_view &str, const std::string_view &sec);
		std::string utf8_to_ansi(const char *szU8);
		std::string UTF8_to_CP1251(const std::string &utf8);
		std::vector<std::string> split(const std::string_view &i_str, const std::string_view &i_delim);
	} // namespace Strings
} // namespace Lippets