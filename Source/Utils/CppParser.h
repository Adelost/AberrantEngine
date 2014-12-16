#pragma once

#include <Utils/StringRef.h>
#include <Utils/Array.h>

#include <regex>
#include <vector>

namespace ae
{
class CppParser
{
public:
	CppParser(const std::string& source)
	{
		m_index = 0;
		m_source = source;
		m_hasNext = true;

		startElement();
		parseNext();
	}
	void parseNext()
	{
		while (hasNext())
		{
			findTokenStart();

			bool tokenMatch = true;

			if (token("\""))
			{
				endElement();
				startElement();

				find("\"");
			}
			else
			{
				m_index++;
			}
		}
	}

	void findTokenStart()
	{
		find("\\S");
	}

	bool hasNext()
	{
		return m_hasNext;
	}

	void find(std::string regex)
	{
		std::regex re(regex);
		std::cmatch m;

		if (std::regex_search(&m_source[m_index], m, re))
		{
			int pos = m.position();
			m_index += pos;

			return;
		}

		m_hasNext = false;
	}

	char get()
	{
		m_source[m_index];
	}

	void next()
	{
		m_index++;
	}

	void foo()
	{
		std::string prefix;

		if (prefix == "\"")
		{
		}
		if (prefix == "\"")
		{
		}
	}

	bool token(const std::string& token)
	{
		int length = token.length();

		if (m_index + length > (int)m_source.length())
			return false;

		return m_source.compare(m_index, length, token) == 0;
	}


	StringRef& last()
	{
		return m_elements.back();
	}

private:
	void startElement()
	{
		m_elements.push_back(StringRef(&m_source, m_index, 0));
	}

	void endElement()
	{
		last().setEnd(m_index);

		Console::print() << "E: " << last().toString();
	}

	int m_index;
	std::string m_source;
	std::vector<StringRef> m_elements;
	bool m_hasNext;
};
}