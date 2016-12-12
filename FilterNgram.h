#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "StringOp.h"
using namespace std;
class CFilterNgram
{
public:
	CFilterNgram(void);
	~CFilterNgram(void);

public:
	void FilterNgram(const string& sInputFile,const string& sOutputFile,int nGram,int threshold);
};

