#include "NkiFile.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <dirent.h>

using namespace std;


void  CNkiFile::_list(const string &sFileFolder, const string& filePath, vector<string> &vecFiles) {
        DIR *dp;
        struct dirent *dirp;
        string prefix;


        if  (filePath.size() > 2 &&  '/' == filePath.at( filePath.size() -1))
        	prefix = filePath.substr(0, filePath.size() - 2);
        else
        	prefix = filePath;

        if ((dp = opendir(sFileFolder.c_str())) == NULL) {
                cout << " Errors occurred  when reading files from directory " << sFileFolder
                                << endl;
                return ;
        }
        while ((dirp = readdir(dp)) != NULL) {
                if ((strcmp(dirp->d_name, ".") == 0)
                                || (strcmp(dirp->d_name, "..") == 0))
                        continue;

                if (dirp->d_type == DT_DIR)
                {
                	_list(sFileFolder + "/" + dirp->d_name, prefix + "/" + dirp->d_name, vecFiles);

                	//vecFiles.insert(file_names.end(), curr_files.begin(), curr_files.end());
                }
                else
                	vecFiles.push_back(prefix + "/" + string(dirp->d_name));

        }
        //return ;
}

CNkiFile::CNkiFile(void)
{
}


CNkiFile::~CNkiFile(void)
{
}
/*********************************************************************************************
函数功能：	返回文件夹sFileFolder下的所有文件名，加载成功，返回true，否则false
参数：		sFileFolder:			文件夹
vecFiles:				返回的文件数组
*********************************************************************************************/
bool CNkiFile::FindAllFiles(const string &sFileFolder, vector<string> &vecFiles)
{
	vecFiles.clear();
	
	string path = "";
	CNkiFile::FindFiles(sFileFolder, path, vecFiles);
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
void CNkiFile::FindFiles(const string &sFileFolder, const string& filePath, vector<string> &vecFiles)
{
	_list(sFileFolder, filePath, vecFiles);

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
	*/
}
