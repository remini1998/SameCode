#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include "SameCode.h"

#define BUFFER_SIZE 100000

using namespace std;

string SameCode::preprocess(string code)
{
	string c(code), r = "";
	// 0为未在此状态，1为行注释，2为块注释。这里不考虑python的``` ```注释的情况
	int commentFlag = 0;
	for (unsigned int a = 0; a < c.size(); a++) {
		char t = c[a];

		if (commentFlag == 1) {
			//处于删除行注释状态
			if (t == '\r' || t == '\n') {
				r.append("\n");
				commentFlag = 0;
			}
			continue;
		}
		if (commentFlag == 2) {
			//处于删除块注释状态
			if (t == '*' && a + 1 < c.size() && t == '/') {
				a++;
				commentFlag = 0;
			}
			continue;
		}

		if (a + 1 < c.size()) {
			//之后还存在其它字符时
			if (c[a] == '/' && c[a + 1] == '/') {
				commentFlag = 1;
				continue;
			}
			else if (c[a] == '/' && c[a + 1] == '*') {
				commentFlag = 2;
				continue;
			}
		}

		//大写变成小写
		if (t >= 'A' && t <= 'Z') t -= 'A' - 'a';
		//一般字母
		if (t >= 'a' && t <= 'z')
			r += t;
		//换行
		//else if (t == '\n' || t == '\r')
		//	r += '\n';
		//其它特殊符号转化为空格
		else r += " ";
	}
	return r;
}

map<string, int> SameCode::countWords(string code)
{
	map<string, int> m;
	for (int a = 0; a < this->keyWordsNum; a++) {
		m[this->keyWords[a]] = 0;
	}
	string tmp = "";
	for (unsigned int a = 0; a < code.size(); a++) {
		if (code[a] != ' ')
			tmp += code[a];
		else
			if (tmp != "") {
				if (m.count(tmp))
					m[tmp]++;
				//以下则发现没有该键时不添加新的
				else if (!isStaticMode)
					m[tmp] = 1;
				tmp = "";
			}
	}
	// 处理最后一个词
	if (tmp != "") {
		if (m.count(tmp))
			m[tmp]++;
		//以下则发现没有该键时不添加新的
		else if (!isStaticMode)
			m[tmp] = 1;
	}
	return m;
}

double SameCode::calcDifference(std::map<std::string, int> code1, std::map<std::string, int> code2)
{
	double result = 0;
	int count = 0;
	for (auto t = code1.begin(); t != code1.end(); t++) {
		if (code2.count(t->first)) {
			count++;
			result += pow(code1[t->first] - code2[t->first], 2);
		}
	}
	result = sqrt(result);
	//以下为标准差算法
	return count ? result / count : 0;
	//以下方差算法
	//return result;
}

std::string SameCode::readFile(std::string fileName)
{
	ifstream ifile(fileName);
	if (!ifile.is_open()) {
		cout << "文件打开失败" << endl;
		return "";
	}
	ostringstream buffer;
	char ch;
	while (ifile.get(ch))
		buffer.put(ch);
	ifile.close();
	return buffer.str();
}
