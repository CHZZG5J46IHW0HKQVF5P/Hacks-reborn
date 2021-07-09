#pragma once
#include "windows.h"
#include <vector>
#include <string>

namespace Lippets
{
	namespace Strings
	{
		inline bool replace(std::string &str, const std::string_view &from, const std::string_view &to)
		{
			size_t start_pos = str.find(from);
			if (start_pos == std::string::npos)
				return false;
			str.replace(start_pos, from.length(), to);
			return true;
		}
		inline std::vector<std::string>::const_iterator get_max_length_string(const std::vector<std::string> &lines)
		{
			std::vector<std::string>::const_iterator max = lines.begin();
			for (size_t i = 1; i < lines.size(); i++)
				if (lines[i].length() > max->length())
					max = lines.begin() + i;
			return max;
		}
		inline std::vector<std::string>::const_iterator get_max_length_string(const std::vector<std::vector<std::string>> &lines)
		{
			std::vector<std::string>::const_iterator max = lines.begin()->begin();
			for (size_t i = 1; i < lines.size(); i++)
				for (size_t n = 0; n < lines[i].size(); n++)
					if (lines[i][n].length() > max->length())
						max = ((lines.begin() + i)->begin() + n);
			return max;
		}
		inline bool isDigit(const std::string_view &str)
		{
			return (str.find_first_not_of("1234567890.") == std::string::npos);
		}
		inline bool strstr(const std::string_view &str, const std::string_view &sec)
		{
			return (str.find(sec) != std::string::npos);
		}
		inline std::string utf8_to_ansi(const char *szU8)
		{
			int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);
			wchar_t* wszString = new wchar_t[wcsLen + 1];
			memset(wszString, 0, wcsLen + 1);
			::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);
			wszString[wcsLen] = '\0';

			int ansiLen = ::WideCharToMultiByte(CP_ACP, NULL, wszString, wcslen(wszString), NULL, 0, NULL, NULL);
			char* szAnsi = new char[ansiLen + 1];
			memset(szAnsi, 0, ansiLen + 1);
			::WideCharToMultiByte(CP_ACP, NULL, wszString, wcslen(wszString), szAnsi, ansiLen, NULL, NULL);
			szAnsi[ansiLen] = '\0';
			std::string sToReturn = szAnsi;
			delete[] szAnsi;
			delete[] wszString;
			return sToReturn;
		}
		inline std::string UTF8_to_CP1251(const std::string &utf8)
		{
			if (!utf8.empty())
			{
				int wchlen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size(), NULL, 0);
				if (wchlen > 0 && wchlen != 0xFFFD)
				{
					std::vector<wchar_t> wbuf(wchlen);
					MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size(), &wbuf[0], wchlen);
					std::vector<char> buf(wchlen);
					WideCharToMultiByte(1251, 0, &wbuf[0], wchlen, &buf[0], wchlen, 0, 0);

					return std::string(&buf[0], wchlen);
				}
			}
			return "";
		}
		inline std::vector<std::string> split(const std::string_view &i_str, const std::string_view &i_delim)
		{
			std::vector<std::string> result;
			size_t found = i_str.find(i_delim);
			size_t startIndex = 0;
			while (found != std::string::npos)
			{
				result.emplace_back(std::string(i_str.begin() + startIndex, i_str.begin() + found));
				startIndex = found + i_delim.size();
				found = i_str.find(i_delim, startIndex);
			}
			if (startIndex != i_str.size())
				result.emplace_back(std::string(i_str.begin() + startIndex, i_str.end()));
			return result;
		}
	} // namespace Strings
} // namespace Lippets


