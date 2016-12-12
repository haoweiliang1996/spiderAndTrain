#pragma once
#include <vector>
#include <fstream>

using namespace std;
class CWordNGram
{
public:
	CWordNGram(void);
	~CWordNGram(void);

	void FindTriGram(const string& sTriGramFile,const string& sSearchFile,const string& outFile);
};

