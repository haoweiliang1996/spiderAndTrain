#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include "structs.h"

#include "separateJudger.h"

using namespace std;

stringstream ss;

//输入：c:\\43.txt
//输出：c:\\43_info.txt
string addInfoAfterName(string filePath, string info) {
	int idx = filePath.find(".");
	if (idx == -1) {
		puts("addInfoToFilePath：输入的是无后缀文件！");
		return filePath;
	}
	string prefix = filePath.substr(0, idx);
	string suffix = filePath.substr(idx, filePath.length() - idx);
	return prefix + info + suffix;
}

void writeDoubleTuple(string outFilePath, map<douNode, int>& dict) {
	ofstream bi(outFilePath.c_str());
	for (map<douNode, int>::iterator it = dict.begin(); it != dict.end(); it++) {
		bi << it->first.left << " " << it->first.right << "\t" << it->second << endl;
	}
	dict.clear();
	bi.close();
}

void writeTripleTuple(string outFilePath, map<triNode, int>& dict) {
	ofstream tri(outFilePath.c_str());
	for (map<triNode, int>::iterator it = dict.begin(); it != dict.end(); it++) {
		tri << it->first.left << " " << it->first.current << " " << it->first.right << "\t" << it->second << endl;
	}
	dict.clear();
	tri.close();
}

void writeTuple(int fileInfo, string outBiFilePath, map<douNode, int>& douMap, string outTriFilePath, map<triNode, int>& triMap) {
	string fileInfoStr;
	ss << "_" << fileInfo;  
	ss >> fileInfoStr; 
	ss.clear();
	printf("~~~输出二元组文件路径：%s\n", addInfoAfterName(outBiFilePath, fileInfoStr).c_str());
	writeDoubleTuple(addInfoAfterName(outBiFilePath, fileInfoStr), douMap);
	printf("~~~输出三元组文件路径：%s\n", addInfoAfterName(outTriFilePath, fileInfoStr).c_str());
	writeTripleTuple(addInfoAfterName(outTriFilePath, fileInfoStr), triMap);
}

const int maxn = 1000;
void solveFiveTuple(string inFilePath, string outBiFilePath, string outTriFilePath) {
	ifstream fin(inFilePath.c_str());
	if (!fin.is_open()) {
		puts("输入文件打开失败！");
		return ;
	}
	string left, current, right, line, fileInfoStr;
	int lDist, rDist, f;
	map<douNode, int> douMap;
	map<triNode, int> triMap;
	int cnt = 0, fileInfo = 0, num = 0;

	///left, lDist, current, rDist, right, f
	while (getline(fin, line)) {
		ss << line;
		ss >> left >> lDist >> current >> rDist >> right >> f;
		ss.clear();
		if (++num % 1000000 == 0)
			printf("已经读取%d行数据\n", num);
		if (SeparateJudger::isSeparate(left) || SeparateJudger::isSeparate(current) || SeparateJudger::isSeparate(right))
			continue;

		//double group count
		if (lDist != 0 || rDist != 0)
			continue;
		if (right == "#End#") {
			douMap[douNode(current, right)] += f;
		}
		douMap[douNode(left, current)] += f;
		
		//triple group count
		triMap[triNode(left, current, right)] += f;
		
		cnt++;
		if (cnt % 3000000 == 0) {
			printf("~~~已经处理%d行数据\n", cnt);
			writeTuple(fileInfo++, outBiFilePath, douMap, outTriFilePath, triMap);
			ss.str("");
		}
	}
	writeTuple(fileInfo++, outBiFilePath, douMap, outTriFilePath, triMap);
	fin.close();
}


int main_bak() {
	string inFilePath, outBiFilePath, outTriFilePath;
	puts("请输入五元组文件路径：");
	cin >> inFilePath;
	int idx = inFilePath.find(".");
	if (idx == -1) {
		puts("输入的是非txt文件！");
		return 1;
	}
	outBiFilePath = addInfoAfterName(inFilePath, "_bi");
	outTriFilePath = addInfoAfterName(inFilePath, "_tri");
	solveFiveTuple(inFilePath, outBiFilePath, outTriFilePath);
}
