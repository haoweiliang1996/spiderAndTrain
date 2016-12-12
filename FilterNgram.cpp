#include "FilterNgram.h"


CFilterNgram::CFilterNgram(void)
{
}


CFilterNgram::~CFilterNgram(void)
{
}
/*
 *功能说明：过滤
*/
void CFilterNgram::FilterNgram(const string& sInputFile,const string& sOutputFile,int nGram,int threshold)
{
	ifstream fin(sInputFile.c_str());
	ofstream fout(sOutputFile.c_str());
	if(!fin.is_open())
	{
		cout<<"cannot open file: "<<sInputFile<<" for input!"<<endl;
		return;
	}

	if(!fout.is_open())
	{
		cout<<"cannot open file: "<<sInputFile<<" for output!"<<endl;
		return;
	}
	string sLine;
	vector<string> wordsVec;
	vector<string> wordVec;
	vector<string> gramVec;
	size_t nCount=0;
	string sLexi;
	string sWord;
	bool flag=false;
	while(getline(fin,sLine))
	{
		CStringOp::Split(gramVec,sLine,"\t");
		if(2==gramVec.size())
		{
			//频次阈值
			if(atoi(gramVec[1].c_str())>=threshold)
			{
				CStringOp::Split(wordsVec,gramVec[0]," ");
				//是否是ngram
				if(wordsVec.size()==nGram)
				{
					int nTotal=0;
					for(int ix=0;ix<nGram;++ix)
					{
						sLexi=wordsVec[ix];
						flag=false;
						//
						CStringOp::Split(wordVec,sLexi,"");
						nCount=wordVec.size();
						
						for(size_t iy=0;iy<nCount;++iy)
						{
							if(CStringOp::CharType(wordVec[iy])==CT_CHINESE)
							{
								flag=true;
							}
						}
						if(!flag)
						{
							nTotal++;
						}
					}
					if(nTotal!=nGram)
					{
						fout<<sLine<<endl;
					}
				}
			}
		}
	}
	fin.close();
	fout.close();
}
//int main()
int main_filterNgram()
{
	string sInputFile,sOutputFile;
	CFilterNgram filter;

	int threshold=0;
	int nGram=0;
	cout<<"请输入处理的ngram文件："<<endl;
	cin>>sInputFile;
	cout<<"请输入处理的ngram文件："<<endl;
	cin>>sOutputFile;
	cout<<"请输入阈值："<<endl;
	cin>>threshold;
	cout<<"请输入ngram的元数："<<endl;
	cin>>nGram;
	cout<<"开始处理...."<<endl;
	filter.FilterNgram(sInputFile,sOutputFile,nGram,threshold);
	cout<<"处理结束！"<<endl;
	return 0;
}