#pragma once
#include <map>
#include <string>
#define MAX_KEY_WORDS 10000
class SameCode {
public:

	// 是否禁用自动根据用户代码修改关键字表
	bool isStaticMode = true;

	// （默认）关键词
	std::string keyWords[MAX_KEY_WORDS] = { "void", "int", "for", "char", "if", "else", "while", "do", "break", "class" };
	
	// （默认）关键词个数
	int keyWordsNum = 10;

	// 按照类中的关键词信息统计个数
	std::map<std::string, int> countWords(std::string code);

	// 输入两个向量，计算不同的程度。注意，这里使用的是标准差算法，不是方差！
	double calcDifference(std::map<std::string, int> code1, std::map<std::string, int> code2);

	// 预处理代码，删除注释，特殊符号，转化为小写等，删除空行
	static std::string preprocess(std::string code);
	
	// 从文件读取到string
	static std::string readFile(std::string fileName);
};