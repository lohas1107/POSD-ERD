#ifndef _PARSER_H_
#define _PARSER_H_

#include <vector>
#include <string>

using namespace std;

class Parser
{
public:
	Parser();
	~Parser();
	static vector<string> split(const string &string, char delim);
	static vector<int> changeToVectorInt(vector<string> stringVector);

private:
	static vector<string>& split(const string &string, char delimiter, vector<std::string> &elements);
};

#endif