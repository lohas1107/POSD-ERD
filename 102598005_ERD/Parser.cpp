#include "Parser.h"
#include <sstream>

const string ZERO = "0";

Parser::Parser()
{
}

Parser::~Parser()
{
}

// ¤Á³Î¦r¦ê
vector<string>& Parser::split(const string &string, char delimiter, vector<std::string> &elements)
{
	stringstream stringstream(string);
	std::string item;
	while (getline(stringstream, item, delimiter))
	{
		elements.push_back(item);
	}
	return elements;
}

// ¨ú±o¤Á³Î¦r¦ê
vector<string> Parser::split(const string &string, char delimiter)
{
	vector<std::string> elements;
	split(string, delimiter, elements);
	return elements;
}

// vector<string> Âà vector<int>
vector<int> Parser::changeToVectorInt(vector<string> stringVector)
{
	vector<int> result;

	for (unsigned i = 0; i < stringVector.size(); i++)
	{
		if (atoi(stringVector[i].c_str()) == 0 && stringVector[i] != ZERO)
		{
			result.push_back(INT_MIN);
		}
		else
		{
			result.push_back(atoi(stringVector[i].c_str()));
		}
	}

	return result;
}
