#pragma once
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
//#include <afx.h>
//#include <io.h>
//#include <direct.h>
#include <stdlib.h>
#include <string.h>
#include "StringOp.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


using namespace std;

const string FilterDic="dic/过滤词条.txt";
const string ProcessedFileList="ProcessedFileList.txt";
const string WordFreqFile="ungram.txt";
const string PosFreqFile="pos.txt";

class CNgram
{
public:
	CNgram(void);
	~CNgram(void);

public:
	void Training(const string& sFileName,const string& sBiGramFileName,const string& sUnGramFileName); //训练一元模型和二元模型


	
	void Training(const string& trainingFileDir,const string& resultFileDir);
	//void CreateFile(const string &sFileFolder,const string& sOutFileFolder);
	//void OutFile(const string& fileName,const string& sOutFile);
	void TrainingWordTriGram(const string& trainingFileDir,const string& resultFileDir);
	void TrainingHybridGram(const string& trainingFileDir,const string& resultFileDir);
	void TrainingWordPosGram(const string& trainingFileDir,const string& resultFileDir);
protected:
	inline void InsertToBiGram(const string& sFirstWord,const string& sSecondWord);
	inline void InsertToUnGram(const string& sWord);
	void PrtBiGramToFile(const string& sFileName);
	void PrtUnGramToFile(const string& sFileName);
	
	void ReadProcessedList(const string& sProcessLstFile);
	void ReadWordFreqFile(const string& sWordFreqFile);
	void ReadPosFreqFile(const string& sPosFreqFile);
	void ReadFilterWord(const string& filterWordFile,vector<string>& filterVec); //读取过滤词条
	bool FindAllFiles(const string &sFileFolder, vector<string> &vecFiles);
	bool CreateDirectory(char* sDirectory);
	void TrainingNGram(const string& sFile,const vector<string>& filterVec);
	inline bool IsFilterString(const string& sentence,const vector<string>& filterVec);
	inline bool IsPunc(const string& str);
	inline void InsertToGramMap(const string& gram);
	inline void InsertToPosGramMap(const string& gram);
	inline void InsertToWordFreqMap(const string& word);
	inline void InsertToPosFreqMap(const string& pos);
	inline void GetWordAndPos(const string& str,string& word,string& pos);
	void GetAllGram(const string& sen);
	void PrtGramToFile(const string& sGramFile);
	void PrtPosGramToFile(const string& sPosGramFile);
	void RecordProcessedFile(const string& sProcessedFileList);
	void PrtWordFreqToFile(const string& sWordFileName);
	void PrtPosFreqToFile(const string& sPosFileName);

	//训练一个文件的字的三元模型
	void TrainTriGram(const string& fileName,const string& outFile,const vector<string>& filterVec);
	void GetAllWordTriGram(const string& sen,map<string,int>& wordTriGramMap);
	void PrtWordTriGram(const string& outFileName,map<string,int>& wordTriGramMap);

	//训练一个文件的分词后的词的二元模型、连续单字散串的三元模型
	void TrainHybridModel(const string& fileName,const string& outBiGramFile,const string& outTriGramFile,const vector<string>& filterVec);
	void GetAllHybridGram(const string& sen,map<string,int>& lexiBigramMap,map<string,int>& lexiTrigramMap);
	void PrtHybridGram(const string& lexiBigramFile,const string& lexiTrigramFile,map<string,int>& lexiBigramMap,map<string,int>& lexiTrigramMap);
	bool isSingleWord(const string& word); //判断是否单字词

	void TrainPosLexiModel(const string& sInFile,const string& s5GramOutFlile,const string& s4PosLexiOutFile,const string& s4Pos2LexiPosOutFile,const string& s3PosLeixOutFile,const vector<string>& vecFilter);
	bool GetAllPosLexiModel(const string& sen,map<string,int>& posLexi5GramMap,map<string,int>& posLexi4GramMap,map<string,int>& pos2LexiPosGramMap,map<string,int>& posWord3GramMap);
	bool GetWordAndPos(vector<string>& vecSen,vector<string>& vecWords,vector<string>& vecPos);
	inline bool InsertToGramMap(map<string,int>& mapGram,const string& sGram)
	{
		if(mapGram.find(sGram)!=mapGram.end())
		{
			mapGram[sGram]=mapGram[sGram]+1;
		}
		else
		{
			mapGram[sGram]=1;
		}
		return true;
	}
	bool PrtPosLexiModel(const string& sFileName,map<string,int>& mapGram);
	void FindFiles(const string &sFileFolder, const string& filePath, vector<string> &vecFiles);
private:
	map<string,int> m_biGramMap; //二元
	map<string,int> m_unGramMap; //一元

	set<string> m_ProcessedList; //已经处理的文件列表
	map<string,int> m_GramMap;  //词的五元组
	map<string,int> m_PosGramMap; //词性的五元组
	map<string,int> m_WordMap; //词频
	map<string,int> m_PosMap;  //词性

	map<string,int> m_triGramMap; //字的三元模型

	//map<string,int> m_lexiBigramMap; //词的二元模型
	//map<string,int> m_lexiTrigramMap; //词的三元模型


	char * itoa(int value,char *string,int radix)
	{
	   int rt=0;
	   if(string==NULL)
	      return NULL;
	   if(radix<=0||radix>30)
	      return NULL;
	   rt=snprintf(string,radix,"%d",value);
	   if(rt>radix)
	      return NULL;
	   string[rt]='\0';
	   return string;
	}

};

