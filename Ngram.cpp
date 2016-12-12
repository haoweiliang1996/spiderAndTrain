#include "Ngram.h"
#include "FileMerge.h"
#include <stdlib.h>
#include <ctime>
#include "main_to3tuple.h"

CNgram::CNgram(void)
{
}


CNgram::~CNgram(void)
{
}

void CNgram::InsertToBiGram(const string& sFirstWord,const string& sSecondWord)
{
	string sBiGram=sFirstWord+" "+sSecondWord;

	if(m_biGramMap.find(sBiGram)!=m_biGramMap.end())
	{
		m_biGramMap[sBiGram]++;
	}
	else
	{
		m_biGramMap[sBiGram]=1;
	}
	return;
}
void CNgram::InsertToUnGram(const string& sWord)
{
	if(m_unGramMap.find(sWord)!=m_unGramMap.end())
	{
		m_unGramMap[sWord]++;
	}
	else
	{
		m_unGramMap[sWord]=1;
	}
	return;
}
void CNgram::PrtBiGramToFile(const string& sFileName)
{
	ofstream fout(sFileName.c_str());
	map<string,int>::const_iterator iter=m_biGramMap.begin();
	map<string,int>::const_iterator iterEnd=m_biGramMap.end();
	if(!fout.is_open())
	{
		cout<<"Cannot open file: "<<sFileName<<" for output!"<<endl;
		return;
	}
	for(;iter!=iterEnd;++iter)
	{
		fout<<iter->first<<"\t"<<iter->second<<endl;
	}
	fout.close();
}
void CNgram::PrtUnGramToFile(const string& sFileName)
{
	ofstream fout(sFileName.c_str());
	map<string,int>::const_iterator iter=m_unGramMap.begin();
	map<string,int>::const_iterator iterEnd=m_unGramMap.end();
	if(!fout.is_open())
	{
		cout<<"Cannot open file: "<<sFileName<<" for output!"<<endl;
		return;
	}
	for(;iter!=iterEnd;++iter)
	{
		fout<<iter->first<<"\t"<<iter->second<<endl;
	}
	fout.close();
}
void CNgram::Training(const string& sFileName,const string& sBiGramFileName,const string& sUnGramFileName)
{
	fstream fin(sFileName.c_str());
	string sLine;
	vector<string> wordVec;
	int nSize=0;
	string sFirstWord,sSecondWord;
	int nCount=0;
	if(!fin.is_open())
	{
		cout<<"Cannot open file: "<<sFileName<<" for input!"<<endl;
		return;
	}
	while(getline(fin,sLine))
	{
		CStringOp::Split(wordVec,sLine," ");
		nSize=wordVec.size()-1;
		nCount++;
		if(nCount%10000==0)
		{
			cout<<"正在处理第"<<nCount<<"行"<<"\t\r";
		}
		for(int ix=0;ix<nSize;++ix)
		{
			sFirstWord=wordVec[ix];
			sSecondWord=wordVec[ix+1];
			//统计一元语法
			InsertToUnGram(sFirstWord);
			//统计最后一个词
			if(ix==nSize-1)
			{
				InsertToUnGram(sSecondWord);
			}
			//统计二元语法
			InsertToBiGram(sFirstWord,sSecondWord);
		}
	}
	fin.close();
	
	//输出到文件
	PrtBiGramToFile(sBiGramFileName);
	PrtUnGramToFile(sUnGramFileName);
}
/*********************************************************************************************
函数功能：	返回文件夹sFileFolder下的所有文件名，加载成功，返回true，否则false
参数：		sFileFolder:			文件夹
vecFiles:				返回的文件数组
*********************************************************************************************/
bool CNgram::FindAllFiles(const string &sFileFolder, vector<string> &vecFiles)
{
	vecFiles.clear();
	string path = "";
	this->FindFiles(sFileFolder, path, vecFiles);
	//std::locale loc = std::locale::global(std::locale(""));
	//CString strTmp; //文件名
	//CFileFind tempFind; 
	//BOOL bFound = tempFind.FindFile((CString)(sFileFolder.c_str()) + "/*");//是否还有文件
	//while (bFound) 
	//{
	//	bFound = tempFind.FindNextFile(); //找下一个文件

	//	if (!tempFind.IsDots())
	//	{
	//		if (!tempFind.IsDirectory())//如果tempFind不是一个目录
	//		{
	//			//得到改文件的文件名，加入到returnFileName中
	//			strTmp = tempFind.GetFileName();
	//			vecFiles.push_back(strTmp.GetBuffer());
	//			strTmp.ReleaseBuffer();

	//		} 
	//	} 
	//} 

	//tempFind.Close();
	//std::locale::global(loc);

	return true;
}

void CNgram::FindFiles(const string &sFileFolder, const string& filePath, vector<string> &vecFiles)
{
	CNkiFile::_list(sFileFolder, filePath, vecFiles);

	//todo
	/*
	cout << "~~~~~~~~~~ " << sFileFolder << endl;
	std::locale loc = std::locale::global(std::locale(""));
	CFileFind tempFind;
	CString strTmp; //文件名
	tempFind.FindFile((CString)(sFileFolder.c_str()));
	tempFind.FindNextFile();
	if (tempFind.IsDirectory())
	{
		BOOL bFound = tempFind.FindFile((CString)(sFileFolder.c_str()) + "/*");//是否还有文件
		while (bFound) 
		{
			bFound = tempFind.FindNextFile(); //找下一个文件

			if (!tempFind.IsDots())
			{
				if (!tempFind.IsDirectory())//如果tempFind不是一个目录
				{
					//得到改文件的文件名，加入到returnFileName中
					strTmp = tempFind.GetFileName();
					vecFiles.push_back(filePath + "/" + strTmp.GetBuffer());
					strTmp.ReleaseBuffer();

				}
				else
				{
					string x = tempFind.GetFileName();
					FindFiles(sFileFolder + "/" + x, filePath + "/" + x, vecFiles);
				}
			} 
		} 
	}
	else
	{
		strTmp = tempFind.GetFileName();
		vecFiles.push_back(filePath + strTmp.GetBuffer());
		strTmp.ReleaseBuffer();
	}
	tempFind.Close();
	std::locale::global(loc);
*/}

bool CNgram::CreateDirectory(char* sDirectory)
{

	char *tag;
	for(tag=sDirectory;*tag;tag++)
	{
	   if (*tag=='/')
	   {
	    	char buf[1000],path[1000];
	    	strcpy(buf,sDirectory);
	    	buf[strlen(sDirectory)-strlen(tag)+1]=NULL;

	    	strcpy(path,buf);
	    	if (access(path,6)==-1)
	    	{
	     		mkdir(path, 0777);
	    	}
	   }
	}
	return true;
}
void CNgram::Training(const string& trainingFileDir,const string& resultFileDir)
{

	vector<string> filesVec;
	string sFileName;
	string sGramFileName,sPosGramFile;
	string sWordFreqFile,sPosFreqFile;
	int nSize=0;
	int index=0;
	string sPath;
	vector<string> filterVec;
	//获得该文件夹的所有文件名称
	if(!FindAllFiles(trainingFileDir,filesVec))
	{
		cout<<"Cannot open FileFolder:"<<trainingFileDir<<endl;
		return;
	}

	sWordFreqFile=resultFileDir+"/WordFreq/"+WordFreqFile;
	sPosFreqFile=resultFileDir+"/WordFreq/"+PosFreqFile;
	CreateDirectory(const_cast<char*>(sWordFreqFile.c_str()));
	CreateDirectory(const_cast<char*>(sPosFreqFile.c_str()));

	//读取过滤词条
	ReadFilterWord(FilterDic,filterVec);
	ReadProcessedList(ProcessedFileList);

	ReadWordFreqFile(sWordFreqFile);
	ReadPosFreqFile(sPosFreqFile);
	nSize=filesVec.size();

	//遍历文件夹中的所有文件
	for(int ix=0;ix<nSize;++ix)
	{
		sFileName=filesVec[ix];
		sPath=trainingFileDir+"/"+sFileName;
		//已处理过，就不再处理
		if(m_ProcessedList.find(sPath)!=m_ProcessedList.end())
		{
			continue;
		}
		index=CStringOp::Find(sFileName,".");
		if(index==string::npos)
		{
			continue;
		}
		//
		cout<<"正在处理第"<<ix<<"文件,文件名为："<<sFileName<<endl;
		sFileName=sFileName.substr(0,index);
		sGramFileName=sFileName+"_ngram.txt";
		sPosGramFile=sFileName+"_posgram.txt";
		sGramFileName=resultFileDir+"/NGram/"+sGramFileName;
		sPosGramFile=resultFileDir+"/PosGram/"+sPosGramFile;

		CreateDirectory(const_cast<char*>(sGramFileName.c_str()));
		CreateDirectory(const_cast<char*>(sPosGramFile.c_str()));

		TrainingNGram(sPath,filterVec);

		PrtGramToFile(sGramFileName);
		PrtPosGramToFile(sPosGramFile);
		
		PrtWordFreqToFile(sWordFreqFile);
		PrtPosFreqToFile(sPosFreqFile);

		//记录已处理的文件
		RecordProcessedFile(sPath);
	}
}
/*
  功能：训练字的三元模型
*/
void CNgram::TrainingWordTriGram(const string& trainingFileDir,const string& resultFileDir)
{
	vector<string> filesVec;
	string sFileName;
	string sGramFileName,sPosGramFile;
	string sWordFreqFile,sPosFreqFile;
	int nSize=0;
	int index=0;
	string sPath;
	vector<string> filterVec;
	//获得该文件夹的所有文件名称
	if(!FindAllFiles(trainingFileDir,filesVec))
	{
		cout<<"Cannot open FileFolder:"<<trainingFileDir<<endl;
		return;
	}
	//读取过滤词条
	ReadFilterWord(FilterDic,filterVec);
	//读取已处理的文件列表
	ReadProcessedList(ProcessedFileList);

	nSize=filesVec.size();

	//遍历文件夹中的所有文件
	for(int ix=0;ix<nSize;++ix)
	{
		sFileName=filesVec[ix];
		sPath=trainingFileDir+"/"+sFileName;
		//已处理过，就不在处理
		if(m_ProcessedList.find(sPath)!=m_ProcessedList.end())
		{
			continue;
		}
		index=CStringOp::Find(sFileName,".");
		if(index==string::npos)
		{
			continue;
		}
		//
		cout<<"正在处理第"<<ix<<"文件,文件名为："<<sFileName<<endl;
		sFileName=sFileName.substr(0,index);
		sGramFileName=sFileName+"_tri_ngram.txt";
		sGramFileName=resultFileDir+"/WordTriGram/"+sGramFileName;

		CreateDirectory(const_cast<char*>(sGramFileName.c_str()));

		TrainTriGram(sPath,sGramFileName,filterVec);;

		//记录已处理的文件
		RecordProcessedFile(sPath);
	}
}
/*
  功能说明：训练一个输入文件的字的三元模型
*/
void CNgram::TrainTriGram(const string& fileName,const string& outFile,const vector<string>& filterVec)
{
	ifstream fin(fileName.c_str());
	string sLine;
	vector<string> senVec;
	int nSize=0;
	if(!fin.is_open())
	{
		cout<<"Cannot open File: "<<fileName<<" for input!"<<endl;
		return;
	}
	map<string,int> wordTriGramMap;
	while(getline(fin,sLine))
	{
		if(sLine=="")
		{
			continue;
		}
		//判断当前行是否过滤行
		if(IsFilterString(sLine,filterVec))
		{
			continue;
		}
		else
		{
			//
			CStringOp::Split(senVec,sLine,"	");
			if(senVec.size()>=3)
			{
				GetAllWordTriGram(senVec[2],wordTriGramMap);
			}
		}
	}
	PrtWordTriGram(outFile,wordTriGramMap);
	fin.close();
}
void CNgram::GetAllWordTriGram(const string& sen,map<string,int>& wordTriGramMap)
{
	size_t nSize=sen.size();
	string firstWord,secondWord,thirdWord;
	string sGram;
	size_t ix=0;
	while(ix<nSize)
	{
		if(ix==0)
		{
			firstWord="#Begin#";
			secondWord="#Begin#";
			//thirdWord=
		}
		if(sen.at(ix)<0)
		{
			thirdWord=sen.substr(ix,2);
			ix=ix+2;

		}
		else
		{
			thirdWord=sen.substr(ix,1);
			ix++;
			while(ix<nSize&&sen.at(ix)>0)
			{
				thirdWord+=sen.substr(ix,1);
				ix++;
			}
		}
		if(thirdWord!=""&&thirdWord!=" "&&thirdWord.find(" ")==string::npos)
		{
			//插入三元
			sGram=firstWord+" "+secondWord+" "+thirdWord;
			if(wordTriGramMap.find(sGram)!=wordTriGramMap.end())
			{
				wordTriGramMap[sGram]++;
			}
			else
			{
				wordTriGramMap[sGram]=1;
			}
			//更改前两个词
			firstWord=secondWord;
			secondWord=thirdWord;
		}
		//处理句尾
		if(ix==nSize)
		{
			thirdWord="#End#";
			sGram=firstWord+" "+secondWord+" "+thirdWord;
			if(wordTriGramMap.find(sGram)!=wordTriGramMap.end())
			{
				wordTriGramMap[sGram]++;
			}
			else
			{
				wordTriGramMap[sGram]=1;
			}
		}
	}
}
/*
 *功能说明输出字的三元组
*/
void CNgram::PrtWordTriGram(const string& outFileName,map<string,int>& wordTriGramMap)
{
	ofstream fout(outFileName.c_str());
	if(!fout.is_open())
	{
		cout<<"Cannot open file: "<<outFileName<<" for output!"<<endl;
		return;
	}
	map<string,int>::const_iterator iter=wordTriGramMap.begin();
	map<string,int>::const_iterator iterEnd=wordTriGramMap.end();

	for(;iter!=iterEnd;++iter)
	{
		fout<<iter->first<<"	"<<iter->second<<endl;
	}
	fout.close();
}
/*
  功能说明：记录已训练的文件
*/
void CNgram::RecordProcessedFile(const string& sProcessedFileName)
{
	ofstream fout(ProcessedFileList.c_str(),ios::app);

	if(!fout.is_open())
	{
		cout<<"Cannot open file: "<<ProcessedFileList<<" for output!"<<endl;
		return;
	}
	fout<<sProcessedFileName<<endl;
	fout.close();
}
/*
  功能说明：训练一个文件的NGram
*/
void CNgram::TrainingNGram(const string& sFile,const vector<string>& filterVec)
{
	ifstream fin(sFile.c_str());
	string sLine;
	vector<string> senVec;
	//vector<string> allSenVec;
	int nSize=0;
	if(!fin.is_open())
	{
		cout<<"Cannot open filterFile: "<<sFile<<" for input!"<<endl;
		return;
	}
	m_GramMap.clear();
	m_PosGramMap.clear();
	//while(getline(fin,sLine))
	//{
	//	if(sLine=="")
	//	{
	//		continue;
	//	}
	//	if(IsFilterString(sLine,filterVec))
	//	{
	//		continue;
	//	}
	//	allSenVec.push_back(sLine);
	//}
	//nSize=allSenVec.size();

	//for(int ix=0;ix<nSize;++ix)
	while(getline(fin,sLine))
	{
		if(sLine=="")
		{
			continue;
		}

		//判断当前行是否过滤行
		if(IsFilterString(sLine,filterVec))
		{
			continue;
		}
		else
		{
			//
			//CStringOp::Split(senVec,sLine,"  ");
			//if(senVec.size()>=3)
			//{
			//	GetAllGram(senVec[2]);
			//}
			GetAllGram(sLine);
		}
		//sLine=allSenVec[ix];
		//CStringOp::Split(senVec,sLine," 	 ");
		//if(senVec.size()>=3)
		//{
		//	GetAllGram(senVec[2]);
		//}
	}
	fin.close();
}
//读取过滤词条
void CNgram::ReadFilterWord(const string& filterWordFile,vector<string>& filterVec)
{
	ifstream fin(filterWordFile.c_str());
	string sLine;

	if(!fin.is_open())
	{
		cout<<"Cannot open filterFile: "<<filterWordFile<<" for input!"<<endl;
		return;
	}
	while(getline(fin,sLine))
	{
		if(sLine==""||CStringOp::Find(sLine,"//")==0)
		{
			continue;
		}
		filterVec.push_back(sLine);
	}

	fin.close();
}
void CNgram::ReadWordFreqFile(const string& sWordFreqFile)
{
	ifstream fin(sWordFreqFile.c_str());
	string sLine;
	vector<string> wordVec;

	if(!fin.is_open())
	{
		cout<<"Cannot open filterFile: "<<sWordFreqFile<<" for input!"<<endl;
		return;
	}
	while(getline(fin,sLine))
	{
		if(sLine=="")
		{
			continue;
		}
		CStringOp::Split(wordVec,sLine,"\t");

		if(wordVec.size()!=2)
		{
			continue;
		}
		m_WordMap[wordVec[0]]=atoi(wordVec[1].c_str());
	}

	fin.close();
}
void CNgram::ReadPosFreqFile(const string& sPosFreqFile)
{
	ifstream fin(sPosFreqFile.c_str());
	string sLine;
	vector<string> posVec;

	if(!fin.is_open())
	{
		cout<<"Cannot open filterFile: "<<sPosFreqFile<<" for input!"<<endl;
		return;
	}
	while(getline(fin,sLine))
	{
		if(sLine=="")
		{
			continue;
		}
		CStringOp::Split(posVec,sLine,"\t");

		if(posVec.size()!=2)
		{
			continue;
		}
		m_PosMap[posVec[0]]=atoi(posVec[1].c_str());
	}

	fin.close();
}
void CNgram::ReadProcessedList(const string& sProcessLstFile) //读取已处理文件列表
{
	ifstream fin(sProcessLstFile.c_str());
	string sLine;

	if(!fin.is_open())
	{
		cout<<"Cannot open filterFile: "<<sProcessLstFile<<" for input!"<<endl;
		return;
	}
	while(getline(fin,sLine))
	{
		if(sLine==""||CStringOp::Find(sLine,"//")==0)
		{
			continue;
		}
		m_ProcessedList.insert(sLine);
	}
	fin.close();
}
//判断是否过滤词条
//返回值：是返回true,否返回false;
inline bool CNgram::IsFilterString(const string& sentence,const vector<string>& filterVec)
{
	string filterWord;
	if(filterVec.size()==0)
	{
		return false;
	}
	int nSize=filterVec.size();
	for(int ix=0;ix<nSize;++ix)
	{
		if(CStringOp::Find(sentence,filterVec[ix])!=string::npos)
		{
			return true;
		}
	}
	return false;
}
//判断是否标点符号
inline bool CNgram::IsPunc(const string& str)
{
	//不带词性标记的串
	size_t index=CStringOp::Find_Last_Of(str,"/");
	string pos;
	if(index==string::npos)
	{
		//判断ASCII吗值
	}
	pos=str.substr(index+1,str.length()-index-1);
	if(pos=="w")
	{
		return true;
	}
	return false;
}
//插入到结构中
inline void CNgram::InsertToGramMap(const string& gram)
{
	if(m_GramMap.find(gram)!=m_GramMap.end())
	{
		m_GramMap[gram]++;
	}
	else
	{
		m_GramMap[gram]=1;
	}
}
//插入到词性五元组
inline void CNgram::InsertToPosGramMap(const string& gram)
{
	if(m_PosGramMap.find(gram)!=m_PosGramMap.end())
	{
		m_PosGramMap[gram]++;
	}
	else
	{
		m_PosGramMap[gram]=1;
	}
}
inline void CNgram::GetWordAndPos(const string& str,string& word,string& pos)
{
	//不带词性标记的串
	size_t index=CStringOp::Find_Last_Of(str,"/");
	if(index==string::npos)
	{
		//没有词性标记
		word=str;
		pos="";
	}
	if(str=="/")
	{
		word="/";
		pos="";
	}
	else
	{
		word=str.substr(0,index);
		pos=str.substr(index+1,str.length()-index-1);
	}
}
void CNgram::GetAllGram(const string& sen)
{
	vector<string> wordVec;
	string currSeg,leftSeg,rightSeg;
	string word,leftWord,rightWord;
	string pos,leftPos,rightPos;
	int leftInterval=0;
	int rightInterval=0;
	char chLeftInterval[2];
	char chRightInterval[2];
	int nSize=0;
	string sGram,sPosGram;

	if(CStringOp::Split(wordVec,sen," "))
	{
		nSize=wordVec.size();
		//进行遍历
		for(int ix=0;ix<nSize;++ix)
		{
			currSeg=wordVec[ix];
			if(IsPunc(currSeg))
			{
				continue;
			}
			GetWordAndPos(currSeg,word,pos);
			leftInterval=0;
			//插入词及词性到词频文件、词性频率文件
			InsertToWordFreqMap(word);
			InsertToPosFreqMap(pos);

			for(int iy=ix-1;iy>ix-3;--iy)
			{
				itoa(leftInterval,chLeftInterval,10);
				if(iy==-2)
				{
					break;
				}
				else if(iy==-1)
				{
					leftWord="#Begin#";
					leftPos="#Begin#";
				}
				else if(IsPunc(wordVec[iy]))
				{
					leftWord="#Begin#";
					leftPos="#Begin#";
					iy=-1;
				}
				else
				{
					leftSeg=wordVec[iy];
					GetWordAndPos(leftSeg,leftWord,leftPos);
				}
				rightInterval=0;
				
				for(int iz=ix+1;iz<ix+3;++iz)
				{
					itoa(rightInterval,chRightInterval,10);
					if(iz==nSize+1)
					{
						break;
					}
					else if(iz==nSize)
					{
						rightWord="#End#";
						rightPos="#End#";
					}
					else if(IsPunc(wordVec[iz]))
					{
						rightWord="#End#";
						rightPos="#End#";
						iz=nSize;
					}
					else
					{
						rightSeg=wordVec[iz];
						GetWordAndPos(rightSeg,rightWord,rightPos);
					}
					
					//拼成五元组
					sGram=leftWord+" "+chLeftInterval+" "+word+" "+chRightInterval+" "+rightWord;
					sPosGram=leftPos+" "+chLeftInterval+" "+pos+" "+chRightInterval+" "+rightPos;
					//插入到结构中
					InsertToGramMap(sGram);
					InsertToPosGramMap(sPosGram);
					++rightInterval;
				}
				++leftInterval;
			}
		}
	}
}
inline void CNgram::InsertToWordFreqMap(const string& word)
{
	if(m_WordMap.find(word)!=m_WordMap.end())
	{
		m_WordMap[word]=m_WordMap[word]+1;
	}
	else
	{
		m_WordMap[word]=1;
	}
}
inline void CNgram::InsertToPosFreqMap(const string& pos)
{
	if(m_PosMap.find(pos)!=m_PosMap.end())
	{
		m_PosMap[pos]=m_PosMap[pos]+1;
	}
	else
	{
		m_PosMap[pos]=1;
	}
}
void CNgram::PrtWordFreqToFile(const string& sWordFileName)
{
	ofstream fout(sWordFileName.c_str());

	if(!fout.is_open())
	{
		cout<<"Cannot open file: "<<sWordFileName<<" for output!"<<endl;
		return;
	}
	map<string,int>::const_iterator iter=m_WordMap.begin();
	map<string,int>::const_iterator iterEnd=m_WordMap.end();
	for(;iter!=iterEnd;++iter)
	{
		fout<<iter->first<<"\t"<<iter->second<<endl;
	}
	fout.close();
}
void CNgram::PrtPosFreqToFile(const string& sPosFileName)
{
	ofstream fout(sPosFileName.c_str());

	if(!fout.is_open())
	{
		cout<<"Cannot open file: "<<sPosFileName<<" for output!"<<endl;
		return;
	}
	map<string,int>::const_iterator iter=m_PosMap.begin();
	map<string,int>::const_iterator iterEnd=m_PosMap.end();
	for(;iter!=iterEnd;++iter)
	{
		fout<<iter->first<<"\t"<<iter->second<<endl;
	}
	fout.close();
}
void CNgram::PrtGramToFile(const string& sGramFile)
{
	ofstream fout(sGramFile.c_str());

	if(!fout.is_open())
	{
		cout<<"Cannot open file: "<<sGramFile<<" for output!"<<endl;
		return;
	}
	map<string,int>::const_iterator iter=m_GramMap.begin();
	map<string,int>::const_iterator iterEnd=m_GramMap.end();

	for(;iter!=iterEnd;++iter)
	{
		fout<<iter->first<<"\t"<<iter->second<<endl;
	}
	fout.close();
}
void CNgram::PrtPosGramToFile(const string& sPosGramFile)
{
	ofstream fout(sPosGramFile.c_str());

	if(!fout.is_open())
	{
		cout<<"Cannot open file: "<<sPosGramFile<<" for output!"<<endl;
		return;
	}
	map<string,int>::const_iterator iter=m_PosGramMap.begin();
	map<string,int>::const_iterator iterEnd=m_PosGramMap.end();

	for(;iter!=iterEnd;++iter)
	{
		fout<<iter->first<<"\t"<<iter->second<<endl;
	}
	fout.close();
}
/*
 *功能说明：训练指定文件夹下所以文件的
*/
void CNgram::TrainingHybridGram(const string& trainingFileDir,const string& resultFileDir)
{
	vector<string> filesVec;
	string sFileName;
	string sGramFileName,sTriGramFileName;
	int nSize=0;
	int index=0;
	string sPath;
	vector<string> filterVec;
	//获得该文件夹的所有文件名称
	if(!FindAllFiles(trainingFileDir,filesVec))
	{
		cout<<"Cannot open FileFolder:"<<trainingFileDir<<endl;
		return;
	}
	//读取过滤词条
	ReadFilterWord(FilterDic,filterVec);
	//读取已处理的文件列表
	ReadProcessedList(ProcessedFileList);

	nSize=filesVec.size();

	//遍历文件夹中的所有文件
	for(int ix=0;ix<nSize;++ix)
	{
		sFileName=filesVec[ix];
		sPath=trainingFileDir+"/"+sFileName;
		//已处理过，就不在处理
		if(m_ProcessedList.find(sPath)!=m_ProcessedList.end())
		{
			continue;
		}
		index=CStringOp::Find(sFileName,".");
		if(index==string::npos)
		{
			continue;
		}
		//
		cout<<"正在处理第"<<ix<<"文件,文件名为："<<sFileName<<endl;
		sFileName=sFileName.substr(0,index);
		sGramFileName=sFileName+"_lexiBigram.txt";
		sGramFileName=resultFileDir+"/LexiBiGram/"+sGramFileName;
		CreateDirectory(const_cast<char*>(sGramFileName.c_str()));

		sTriGramFileName=sFileName+"_wordTrigram.txt";
		sTriGramFileName=resultFileDir+"/SingleWordTriGram/"+sTriGramFileName;
		CreateDirectory(const_cast<char*>(sTriGramFileName.c_str()));

		TrainHybridModel(sPath,sGramFileName,sTriGramFileName,filterVec);;

		//记录已处理的文件
		RecordProcessedFile(sPath);
	}
}
/*
*功能说明：训练混合模型：词的二元模型，连续单字散串的三元模型
*/
void CNgram::TrainHybridModel(const string& fileName,const string& outBiGramFile,const string& outTriGramFile,const vector<string>& filterVec)
{
	ifstream fin(fileName.c_str());
	string sLine;
	vector<string> senVec;
	int nSize=0;
	if(!fin.is_open())
	{
		cout<<"Cannot open File: "<<fileName<<" for input!"<<endl;
		return;
	}
	map<string,int> lexiBigramMap;
	map<string,int> lexiTrigramMap;
	while(getline(fin,sLine))
	{
		if(sLine=="")
		{
			continue;
		}
		//判断当前行是否过滤行
		if(IsFilterString(sLine,filterVec))
		{
			continue;
		}
		else
		{
			//
			CStringOp::Split(senVec,sLine,"	");
			if(senVec.size()>=3)
			{
				GetAllHybridGram(senVec[2],lexiBigramMap,lexiTrigramMap);
			}
		}
	}
	PrtHybridGram(outBiGramFile,outTriGramFile,lexiBigramMap,lexiTrigramMap);
	fin.close();
}
/*
 *功能说明：取得词的二元和单字词的三元模型
*/
void CNgram::GetAllHybridGram(const string& sen,map<string,int>& lexiBigramMap,map<string,int>& lexiTrigramMap)
{
	vector<string> wordVec;
	CStringOp::Split(wordVec,sen," ");
	string puncs=",.;?!，。？！；——…";
	size_t nSize=wordVec.size();
	size_t ix=0;
	size_t index=0;
	string word,punc;
	string firstWord,secondWord,thirdWord;
	string firstLexi,secondLexi;
	
	string biGram,triGram;
	size_t nLen=0;
	for(;ix<=nSize;++ix)
	{
		if(0==ix)
		{
			firstWord="#Begin#";
			secondWord="#Begin#";

			firstLexi="#Begin#";
		}
		if(nSize==ix)
		{
			thirdWord="#End#";

			secondLexi="#End#";
		}
		else
		{
			nLen=wordVec[ix].size();
			//判断当前字符类型
			index=CStringOp::Find_Last_Of(wordVec[ix],"/");
			if(index!=string::npos)
			{
				punc=wordVec[ix].substr(index+1,nLen-index-1);
				word=wordVec[ix].substr(0,index);
			}
			else
			{
				punc="";
				word=wordVec[ix];
			}
			if(""==word)
			{
				continue;
			}
			
			//是预定义标点符号
			if("w"==punc&&CStringOp::Find(puncs,word)!=string::npos)
			{
				secondLexi="#End#";
				thirdWord="#End#";
			}
			else
			{
				secondLexi=word;
				thirdWord=word;
			}
		}
		biGram=firstLexi+" "+secondLexi;
		if(lexiBigramMap.find(biGram)!=lexiBigramMap.end())
		{
			lexiBigramMap[biGram]=lexiBigramMap[biGram]+1;
		}
		else
		{
			lexiBigramMap[biGram]=lexiBigramMap[biGram]+1;
		}
		triGram=firstWord+" "+secondWord+" "+thirdWord;
		//三个连续单字
		if(isSingleWord(firstWord)&&isSingleWord(secondWord)&&isSingleWord(thirdWord))
		{
			//插入到结构中
			if(lexiTrigramMap.find(triGram)!=lexiTrigramMap.end())
			{
				lexiTrigramMap[triGram]=lexiTrigramMap[triGram]+1;
			}
			else
			{
				lexiTrigramMap[triGram]=1;
			}
		}
		else if("#Begin#"==firstWord&&isSingleWord(secondWord)&&isSingleWord(thirdWord))
		{
			//插入到结构中
			if(lexiTrigramMap.find(triGram)!=lexiTrigramMap.end())
			{
				lexiTrigramMap[triGram]=lexiTrigramMap[triGram]+1;
			}
			else
			{
				lexiTrigramMap[triGram]=1;
			}
		}
		else if(isSingleWord(firstWord)&&isSingleWord(secondWord)&&"#End#"==thirdWord)
		{
			//插入到结构中
			if(lexiTrigramMap.find(triGram)!=lexiTrigramMap.end())
			{
				lexiTrigramMap[triGram]=lexiTrigramMap[triGram]+1;
			}
			else
			{
				lexiTrigramMap[triGram]=1;
			}
		}
		if("#End#"==secondLexi)
		{
			firstLexi="#Begin#";

			firstWord="#Begin#";
			secondWord="#Begin#";
		}
		else
		{
			firstLexi=secondLexi;

			firstWord=secondWord;
			secondWord=thirdWord;
		}
		//如果是句子末尾，且是标点符号，则插入后退出，不在统计句子末尾标记
		if(nSize-1==ix)
		{
			if(CStringOp::Find(puncs,punc)!=string::npos)
			{
				break;
			}
		}
	}
}
 /*
 *判断是否单字词:true是单字汉字词或数字串或英文单词，false不是
 */
bool CNgram::isSingleWord(const string& word)
{
	size_t nSize=word.size();
	if(nSize==0)
	{
		return false;
	}
	//判断是否是数字或字母
	if(1==nSize)
	{
		if(word.at(0)>='0'&&word.at(0)<='9'||word.at(0)>='a'&&word.at(0)<='z'||word.at(0)>='A'&&word.at(0)<='Z')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if(nSize!=2)
	{
		//判断是否是数字串或ASCII吗串
		if(word.at(0)<0)
		{
			return false;
		}
		else
		{
			size_t ix=0;
			
			while(ix<nSize)
			{
				if(word.at(ix)>0)
				{
					if(word.at(ix)>='0'&&word.at(ix)<='9'||word.at(ix)>='a'&&word.at(ix)<='z'||word.at(ix)>='A'&&word.at(ix)<='Z')
					{
						ix++;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			if(nSize==ix)
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		if(CStringOp::CharType(word)==CT_CHINESE)
		{
			return true;
		}
	}
	return false;
}
/*
*输出统计好的模型（词的二元和单字词的三元）
*/
void CNgram::PrtHybridGram(const string& lexiBigramFile,const string& lexiTrigramFile,map<string,int>& lexiBigramMap,map<string,int>& lexiTrigramMap)
{
	ofstream fOutBigram(lexiBigramFile.c_str());
	ofstream fOutTrigram(lexiTrigramFile.c_str());
	if(!fOutBigram.is_open())
	{
		cout<<"Error open file: "<<lexiBigramFile<<" for output!"<<endl;
		return;
	}
	if(!fOutTrigram.is_open())
	{
		cout<<"Error open file: "<<lexiTrigramFile<<" for output!"<<endl;
		return;
	}
	map<string,int>::const_iterator iter=lexiBigramMap.begin();
	map<string,int>::const_iterator iterEnd=lexiBigramMap.end();
	for(;iter!=iterEnd;++iter)
	{
		fOutBigram<<iter->first<<"\t"<<iter->second<<endl;
	}
	iter=lexiTrigramMap.begin();
	iterEnd=lexiTrigramMap.end();
	for(;iter!=iterEnd;++iter)
	{
		fOutTrigram<<iter->first<<"\t"<<iter->second<<endl;
	}
	fOutBigram.close();
	fOutTrigram.close();
}
//void CNgram::CreateFile(const string &sFileFolder,const string& sOutFileFolder)
//{
//	vector<string> vecFile;
//	FindAllFiles(sFileFolder,vecFile);
//
//	int nSize=vecFile.size();
//	string sPath,sOutPath;
//
//	for(int ix=0;ix<nSize;++ix)
//	{
//		sPath=sFileFolder+"/"+vecFile[ix];
//
//		sOutPath=sOutFileFolder+"/"+vecFile[ix];
//
//		OutFile(sPath,sOutPath);
//	}
//}
//void CNgram::OutFile(const string& fileName,const string& sOutFile)
//{
//	ifstream fin(fileName.c_str());
//	ofstream fout(sOutFile.c_str());
//	string sLine;
//	int count=0;
//	int counter=0;
//
//	while(getline(fin,sLine))
//	{
//		if(sLine=="")
//		{
//			continue;
//		}
//		if(counter==150)
//		{
//			break;
//		}
//		if(count%2000==0||count%2001==0)
//		{
//			fout<<sLine<<endl;
//			counter++;
//		}
//		count++;
//	}
//	fin.close();
//	fout.close();
//}

/*
*功能说明：训练词与词性的混合模型
*
*/
void CNgram::TrainingWordPosGram(const string& trainingFileDir,const string& resultFileDir)
{
	vector<string> filesVec;
	string sFileName;
	string sGramFileName,s4GramFileName,s4PosGramFileName,sTriPosLexiFileName;
	int nSize=0;
	int index=0;
	string sPath;
	vector<string> filterVec;
	//获得该文件夹的所有文件名称
	if(!FindAllFiles(trainingFileDir,filesVec))
	{
		cout<<"Cannot open FileFolder:"<<trainingFileDir<<endl;
		return;
	}
	//读取过滤词条
	ReadFilterWord(FilterDic,filterVec);
	//读取已处理的文件列表
	ReadProcessedList(ProcessedFileList);

	nSize=filesVec.size();

	//遍历文件夹中的所有文件
	for(int ix=0;ix<nSize;++ix)
	{
		sFileName=filesVec[ix];
		sPath=trainingFileDir+"/"+sFileName;
		//已处理过，就不在处理
		if(m_ProcessedList.find(sPath)!=m_ProcessedList.end())
		{
			continue;
		}
		index=CStringOp::Find(sFileName,".");
		if(index==string::npos)
		{
			continue;
		}
		//
		cout<<"正在处理第"<<ix<<"文件,文件名为："<<sFileName<<endl;

		sFileName=sFileName.substr(0,index);
		
		// 格式（pos, word2, pos2, word3, pos3）
		sGramFileName=sFileName+"_lexiPos5.txt";
		sGramFileName=resultFileDir+"/LexiPos5Gram/"+sGramFileName;
		CreateDirectory(const_cast<char*>(sGramFileName.c_str()));

		//格式（pos, word2, pos2, word3）
		s4GramFileName=sFileName+"_4posLexiGram.txt";
		s4GramFileName=resultFileDir+"/PosLexi4Gram/"+s4GramFileName;
		CreateDirectory(const_cast<char*>(s4GramFileName.c_str()));

		//格式（pos, word2, word3, pos3）
		s4PosGramFileName=sFileName+"_Pos2LexiPosLexiGram.txt";
		s4PosGramFileName=resultFileDir+"/Pos2LexiPosLexiGram/"+s4PosGramFileName;
		CreateDirectory(const_cast<char*>(s4PosGramFileName.c_str()));

		//格式（pos, word2, word3）
		sTriPosLexiFileName=sFileName+"_3PosLexi.txt";
		sTriPosLexiFileName=resultFileDir+"/3PosLexi/"+sTriPosLexiFileName;
		CreateDirectory(const_cast<char*>(sTriPosLexiFileName.c_str()));

		//TrainHybridModel(sPath,sGramFileName,sTriPosLexiFileName,filterVec);;
		TrainPosLexiModel(sPath,sGramFileName,s4GramFileName,s4PosGramFileName,sTriPosLexiFileName,filterVec);
		//记录已处理的文件
		RecordProcessedFile(sPath);
	}
}
void  CNgram::TrainPosLexiModel(const string& sInFile,const string& s5GramOutFlile,const string& s4PosLexiOutFile,const string& s4Pos2LexiPosOutFile,const string& s3PosLeixOutFile,const vector<string>& vecFilter)
{
	ifstream fin(sInFile.c_str());
	string sLine;
	vector<string> senVec;
	int nSize=0;
	if(!fin.is_open())
	{
		cout<<"Cannot open File: "<<sInFile<<" for input!"<<endl;
		return;
	}
	map<string,int> posLexi5GramMap;
	map<string,int> posLexi4GramMap;
	map<string,int> pos2LexiPosGramMap;
	map<string,int> posWord3GramMap;

	while(getline(fin,sLine))
	{
		if(sLine=="")
		{
			continue;
		}
		//判断当前行是否过滤行
		if(IsFilterString(sLine,vecFilter))
		{
			continue;
		}
		else
		{
			//
			GetAllPosLexiModel(sLine,posLexi5GramMap,posLexi4GramMap,pos2LexiPosGramMap,posWord3GramMap);
		}
	}
	PrtPosLexiModel(s5GramOutFlile,posLexi5GramMap);
	PrtPosLexiModel(s4PosLexiOutFile,posLexi4GramMap);
	PrtPosLexiModel(s4Pos2LexiPosOutFile,pos2LexiPosGramMap);
	PrtPosLexiModel(s3PosLeixOutFile,posWord3GramMap);
	fin.close();
}
/*
*功能说明：训练句子的词性与词的混合模型
*/
bool CNgram::GetAllPosLexiModel(const string& sen,map<string,int>& posLexi5GramMap,map<string,int>& posLexi4GramMap,map<string,int>& pos2LexiPosGramMap,map<string,int>& posWord3GramMap)
{
	vector<string> vecSen;
	CStringOp::Split(vecSen,sen," ");
	size_t nSize=vecSen.size();
	if(vecSen.size()<3)
	{
		return false;
	}
	string pos,pos2,pos3;
	string word,word2,word3;
	vector<string> vecWord,vecPos;
	string sGram;
	if(!GetWordAndPos(vecSen,vecWord,vecPos))
	{
		return false;
	}
	for(size_t ix=0;ix<nSize;++ix)
	{
		if(ix+2<nSize)
		{
			pos=vecPos[ix];
			word=vecWord[ix];

			pos2=vecPos[ix+1];
			word2=vecWord[ix+1];

			pos3=vecPos[ix+2];
			word3=vecWord[ix+2];

			if(pos==""||pos2==""||pos3=="")
			{
				continue;
			}

			//统计混合模型
			sGram=pos+" "+word2+" "+pos2+" "+word3+" "+pos3;
			InsertToGramMap(posLexi5GramMap,sGram);

			sGram=pos+" "+word2+" "+pos2+" "+word3;
			InsertToGramMap(posLexi4GramMap,sGram);

			sGram=pos+" "+word2+" "+word3+" "+pos3;
			InsertToGramMap(pos2LexiPosGramMap,sGram);

			sGram=pos+" "+word2+" "+word3;

			InsertToGramMap(posWord3GramMap,sGram);
		}
	}
	return true;
}
/*
*功能说明：对词性标注的句子，分别取出词与词性
*参数说明：
*	vecSen:分词后的句子
*	vecWords:句子中词的数组
*	vecPos:对应的词性的数组
*/
bool CNgram::GetWordAndPos(vector<string>& vecSen,vector<string>& vecWords,vector<string>& vecPos)
{
	size_t nSize=vecSen.size();
	vecWords.clear();
	vecPos.clear();
	vecWords.resize(nSize,"");
	vecPos.resize(nSize,"");
	size_t ix=0;
	string str;
	string sWord,sPos;
	size_t index=0;
	size_t nLen=0;

	if(0==nSize)
	{
		return false;
	}

	for(ix=0;ix<nSize;++ix)
	{
		str=vecSen[ix];
		nLen=vecSen[ix].size();
		index=CStringOp::Find_Last_Of(vecSen[ix],"/");
		if(index!=string::npos)
		{
			sPos=vecSen[ix].substr(index+1,nLen-index-1);

			sWord=vecSen[ix].substr(0,index);
			//20140625添加，将空格作为标点符号，在split的时候由于按空格split，将空格去掉了：
			//例如：3.1/m  /w  气候/n  特征/n
			if(sWord=="")
			{
				sWord=" ";
			}
		}
		else
		{
			sPos="";
			sWord=vecSen[ix];
		}
		vecWords[ix]=sWord;
		vecPos[ix]=sPos;
	}

	return true;
}
/*
*
*功能说明：输出混合模型到文件中
*/
bool CNgram::PrtPosLexiModel(const string& sFileName,map<string,int>& mapGram)
{
	ofstream fOut(sFileName.c_str());

	if(!fOut.is_open())
	{
		cout<<"Cannot open file:" <<sFileName<<" for output!"<<endl;
		return false;
	}
	map<string,int>::const_iterator iter=mapGram.begin();
	map<string,int>::const_iterator iterEnd=mapGram.end();


	for(;iter!=iterEnd;++iter)
	{
		fOut<<iter->first<<"\t"<<iter->second<<endl;
	}
	fOut.close();
	return true;
}
//
//
//获得当前时间
//
string Now()
{
	time_t t = time(0);
    char tmp[32];
    strftime(tmp, sizeof(tmp), "[%Y-%m-%d %X]", localtime(&t));
	return string(tmp);
}
//int main_ngram()
int main(int argc, char ** argv)
{
	CNgram ngram;
	//string puncs=",.;?!，。？！；——…";
	//string str;
	//while(true)
	//{
	//	cin>>str;
	//	if(CStringOp::Find(puncs,str)!=string::npos)
	//	//if(ngram.isSingleWord(str))
	//	{
	//		cout<<"合法"<<endl;
	//	}
	//	else
	//	{
	//		cout<<"不合法"<<endl;
	//	}
	//}

	string sTrainDir,sOutDir;

	if (argc == 3)
	{
		sTrainDir = argv[1];
		sOutDir = argv[2];
		cout << "sTrainDir:" <<  sTrainDir << endl;
		cout << "sOutDir:" <<  sOutDir << endl;
	}
	else if (1 == argc)
	{

	cout<<"请输入训练语料路径:"<<endl;
	cin>>sTrainDir;
	cout<<"请输入统计结果路径："<<endl;
	cin>>sOutDir;

	}
	else
	{
		cout << "usage: " << argv[0] <<  " sTrainDir sOutDir" <<endl;
		return 1;
	}
	

	cout<<"开始训练时间："<<Now()<<endl;
		//训练五元组
		ngram.Training(sTrainDir,sOutDir);

	CFileMerge fm;
	
	string mergedFile =  sOutDir + "/merge.txt";

	//对已经处理好的Ｎgram进行统计等
	fm.MergeFile(sOutDir + "/NGram", mergedFile);



	string outBiFilePath = addInfoAfterName(mergedFile, "_bi");
	string outTriFilePath = addInfoAfterName(mergedFile, "_tri");
	solveFiveTuple(mergedFile, outBiFilePath, outTriFilePath);


	//训练字的三元模型
	//ngram.TrainingWordTriGram(sTrainDir,sOutDir);

	//20140723训练词的二元模型和单字词的三元模型
	//ngram.TrainingHybridGram(sTrainDir,sOutDir);
	
	//20140723训练词与词性的混合模型
	//ngram.TrainingWordPosGram(sTrainDir,sOutDir);
	cout<<"结束训练时间："<<Now()<<endl;
	return 0;
}
