#include "FileMerge.h"

typedef struct _Node{
                int freq;
                vector<int> finIndexVec;
        }Node;


CFileMerge::CFileMerge(void)
{
}


CFileMerge::~CFileMerge(void)
{
}
/*
 *功能说明：对文件进行合并
*/
bool CFileMerge::MergeFile(const string &fileDirectory,const string& outFile)
{

	long lineCount = 0;
	vector<string> fileVec;
	vector<ifstream*> finVec;
	vector<int> hasNext;
	string sFileName="";
	size_t nFileCount=0;
	string gram;
	int freq=0;
	string line="";
	//struct Node{
	//	int freq;
	//	vector<int> finIndexVec;
	//};
	//设定打开文件限制
	//_setmaxstdio(2000);
	ofstream fout(outFile.c_str());
	//获取所有的文件
	if(CNkiFile::FindAllFiles(fileDirectory,fileVec))
	{

		//////////////debug/////////////
		for(size_t j = 0; j < fileVec.size(); j ++)
			cout<<  "File " << fileVec[j] << " is to be processed!"   << endl;
		//////////////debug ends/////////////

		nFileCount=fileVec.size();
		finVec.resize(nFileCount,NULL);
		hasNext.resize(nFileCount,1);
		//FILE* *farray = new FILE*[nFileCount];
		//初始化文件流
		for(int ix=0;ix<nFileCount;++ix)
		{
			sFileName=fileVec[ix];
			sFileName=fileDirectory+"/"+sFileName;
			//char* fileName = sFileName.c_str();
             //farray[ix] = fopen(sFileName.c_str(), "rt");
             //free(fileName);
			ifstream* fin=new ifstream(sFileName.c_str());
			finVec.push_back(fin);
			if(fin->is_open())
			{
				//finVec.push_back(fin);
				finVec[ix]=fin;
			}
			else
			{
				cout<<sFileName<<"打开出错"<<endl;
			}
		}
		map<string,Node> dataMap;
		//取出第一行数据放入到dataMap中
		for(int ix=0;ix<nFileCount;++ix)
		{
			cout<<"读取第"<<ix<<"个文件"<<endl;
			cout<<fileVec[ix]<<endl;
			//char line[4096];
			if(getline(*finVec[ix],line))
			//if(fscanf(farray[ix], "%s", line))
			//if(fgets(line,4096,farray[ix]))
			{
				//
				vector<string> tmpVec;
				CStringOp::Split(tmpVec,line,"	");
				gram=tmpVec[0];
				freq=atoi(tmpVec[1].c_str());
				if(dataMap.find(gram)!=dataMap.end())
				{
					dataMap[gram].freq=dataMap[gram].freq+freq;
					dataMap[gram].finIndexVec.push_back(ix);
				}
				else
				{
					Node node;
					node.freq=freq;
					vector<int> tmpIndexVec;
					tmpIndexVec.push_back(ix);
					node.finIndexVec=tmpIndexVec;
					dataMap[gram]=node;
				}
			}
			else
			{
				hasNext[ix]=0;
			}
		}
		//合并输出
		while(true)
		{
			//没有就合并结束
			if(dataMap.size()==0)
			{
				break;
			}
			//输出map中的第一个元素
			map<string,Node>::iterator iter=dataMap.begin();
			fout<<iter->first<<"\t"<<iter->second.freq<<endl;
			//cout<<iter->first<<"\t"<<iter->second.freq<< "---"<< dataMap.size() <<   endl;

			//输出即删除
			vector<int> toDel = iter->second.finIndexVec;

			dataMap.erase(dataMap.begin());

			size_t nCount=toDel.size();
			vector<string> nextDataVec;
			//读取最小行的文件的下一行
			for(int iy=0;iy<nCount;++iy)
			{
				int index=toDel[iy];
				//if(fscanf(farray[iy], "%s", line))
				if(getline(*finVec[index],line))
				{
					if (0 == ((lineCount ++) % 10000)) 
						cout << "已经读入" <<  lineCount -1  << "行" << endl;
					vector<string> tmpVec;

					//cout << line << "from file " << index << endl;

					CStringOp::Split(tmpVec,line,"	");
					if(tmpVec.size()==2)
					{
						gram=tmpVec[0];
						freq=atoi(tmpVec[1].c_str());
						if(dataMap.find(gram)!=dataMap.end())
						{
							dataMap[gram].freq=dataMap[gram].freq+freq;
							dataMap[gram].finIndexVec.push_back(index);
						}
						else
						{
							Node node;
							node.freq=freq;
							vector<int> tmpIndexVec;
							tmpIndexVec.push_back(index);
							node.finIndexVec=tmpIndexVec;
							dataMap[gram]=node;
						}
					}
				}
				else
				{
					hasNext[index]=0;
				}
			}
		}

		for(int i = 0; i < nFileCount; ++i)
		{
			finVec[i]->close();
			//fclose(farray[i]);
		}
        //delete [] farray;
		fout.close();
		return true;
	}
	return false;
}
//
//
//获得当前时间
//
string NowTime()
{
	time_t t = time(0);
    char tmp[32];
    strftime(tmp, sizeof(tmp), "[%Y-%m-%d %X]", localtime(&t));
	return string(tmp);
}
int main2()
{
	CFileMerge fm;
	string sTrainDir,sOutDir;
	cout<<"请输入合并文件路径:"<<endl;
	cin>>sTrainDir;
	cout<<"请输入结果路径："<<endl;
	cin>>sOutDir;
	cout<<"开始合并时间："<<NowTime()<<endl;
	fm.MergeFile(sTrainDir,sOutDir);
	cout<<"结束训练时间："<<NowTime()<<endl;
	return 0;
}
