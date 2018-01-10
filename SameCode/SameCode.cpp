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
	// 0Ϊδ�ڴ�״̬��1Ϊ��ע�ͣ�2Ϊ��ע�͡����ﲻ����python��``` ```ע�͵����
	int commentFlag = 0;
	for (unsigned int a = 0; a < c.size(); a++) {
		char t = c[a];

		if (commentFlag == 1) {
			//����ɾ����ע��״̬
			if (t == '\r' || t == '\n') {
				r.append("\n");
				commentFlag = 0;
			}
			continue;
		}
		if (commentFlag == 2) {
			//����ɾ����ע��״̬
			if (t == '*' && a + 1 < c.size() && t == '/') {
				a++;
				commentFlag = 0;
			}
			continue;
		}

		if (a + 1 < c.size()) {
			//֮�󻹴��������ַ�ʱ
			if (c[a] == '/' && c[a + 1] == '/') {
				commentFlag = 1;
				continue;
			}
			else if (c[a] == '/' && c[a + 1] == '*') {
				commentFlag = 2;
				continue;
			}
		}

		//��д���Сд
		if (t >= 'A' && t <= 'Z') t -= 'A' - 'a';
		//һ����ĸ
		if (t >= 'a' && t <= 'z')
			r += t;
		//����
		//else if (t == '\n' || t == '\r')
		//	r += '\n';
		//�����������ת��Ϊ�ո�
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
				//��������û�иü�ʱ������µ�
				else if (!isStaticMode)
					m[tmp] = 1;
				tmp = "";
			}
	}
	// �������һ����
	if (tmp != "") {
		if (m.count(tmp))
			m[tmp]++;
		//��������û�иü�ʱ������µ�
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
	//����Ϊ��׼���㷨
	return count ? result / count : 0;
	//���·����㷨
	//return result;
}

std::string SameCode::readFile(std::string fileName)
{
	ifstream ifile(fileName);
	if (!ifile.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		return "";
	}
	ostringstream buffer;
	char ch;
	while (ifile.get(ch))
		buffer.put(ch);
	ifile.close();
	return buffer.str();
}
