#pragma once
#include <fstream>
#include <map>
#include <iostream>
#include <stdlib.h>
#include "NkiFile.h"
#include "StringOp.h"
class CFileMerge
{
public:
	CFileMerge(void);
	~CFileMerge(void);

	bool MergeFile(const string &fileDirectory,const string& outFile);
};

