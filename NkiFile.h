#pragma once
#include <vector>
#include <string>
//#include <afx.h>
//#include <io.h>
//#include <direct.h>

using namespace std;
class CNkiFile
{
public:
	CNkiFile(void);
	~CNkiFile(void);

	static bool FindAllFiles(const string &sFileFolder, vector<string> &vecFiles);
	static void FindFiles(const string &sFileFolder, const string& filePath, vector<string> &vecFiles);
	static void _list(const string &sFileFolder, const string& filePath, vector<string> &vecFiles);



};

