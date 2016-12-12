#pragma once
#include <string>
#include <vector>
#include "CPublicDefine.h"
using namespace std;
class CStringOp
{
public:
	CStringOp(void);
	~CStringOp(void);

public:
	static size_t Find(const string& str, const string& sub);
	static size_t Find_Last_Of(const string& str, const string& sub);
	static size_t FindAny(const string& str, const vector<string>& subs, string& foundStr);
	static bool Split(vector<string> &arrResult, const string& strSource, const string& strSep);
	static vector<string> Split(const string& strSource, const vector<string>& strsSep, const bool remove_null, const bool remove_sep);
	static vector<string> getSequence(const string& str);
	static string tolowercase(const string& str);
	static string trim(const string& str,const string& delimiter=" "); //默认空格
	static int CharType(const string& str);
};