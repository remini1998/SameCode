#pragma once
#include <map>
#include <string>
#define MAX_KEY_WORDS 10000
class SameCode {
public:

	// �Ƿ�����Զ������û������޸Ĺؼ��ֱ�
	bool isStaticMode = true;

	// ��Ĭ�ϣ��ؼ���
	std::string keyWords[MAX_KEY_WORDS] = { "void", "int", "for", "char", "if", "else", "while", "do", "break", "class" };
	
	// ��Ĭ�ϣ��ؼ��ʸ���
	int keyWordsNum = 10;

	// �������еĹؼ�����Ϣͳ�Ƹ���
	std::map<std::string, int> countWords(std::string code);

	// �����������������㲻ͬ�ĳ̶ȡ�ע�⣬����ʹ�õ��Ǳ�׼���㷨�����Ƿ��
	double calcDifference(std::map<std::string, int> code1, std::map<std::string, int> code2);

	// Ԥ������룬ɾ��ע�ͣ�������ţ�ת��ΪСд�ȣ�ɾ������
	static std::string preprocess(std::string code);
	
	// ���ļ���ȡ��string
	static std::string readFile(std::string fileName);
};