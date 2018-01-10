#include <iostream>
#include "SameCode.h"
//#define TEST

using namespace std;

int test() {
	std::string code1, code2, code3;
	code1 = SameCode::readFile("code1.cpp");
	code2 = SameCode::readFile("code2.cpp");
	code3 = SameCode::readFile("code3.cpp");
	
	SameCode sc;
	code1 = SameCode::preprocess(code1);
	code2 = SameCode::preprocess(code2);
	code3 = SameCode::preprocess(code3);

	auto result1 = sc.countWords(code1);
	auto result2 = sc.countWords(code2);
	auto result3 = sc.countWords(code3);

	double result12 = sc.calcDifference(result1, result2);
	double result13 = sc.calcDifference(result1, result3);

	std::cout << "code1.cpp与code2.cpp差异度为" << result12 << std::endl;
	std::cout << "code1.cpp与code3.cpp差异度为" << result13 << std::endl;

	return 0;
}

void help() {
	cout << "-h 或 --help\t\t\t\t\t显示帮助" << endl;
	cout << "(-c/--compare) [文件1路径] [文件2路径] \t\t计算文件1和文件2的差异度" << endl;
	cout << "末尾添加 -d 或 --dynamic\t\t\t开启动态模式（提高要求）" << endl;
}

void compare(SameCode& sc, string file1, string file2) {

	std::string code1, code2;
	code1 = SameCode::readFile(file1);
	code2 = SameCode::readFile(file2);

	code1 = SameCode::preprocess(code1);
	code2 = SameCode::preprocess(code2);

	auto result1 = sc.countWords(code1);
	auto result2 = sc.countWords(code2);

	double result = sc.calcDifference(result1, result2);

	std::cout << file1 << "与"<< file2 << "差异度为" << result << std::endl;

	return;
}

int main(int argc, char* argv[]) {
#ifdef TEST
	return test();
#else

	if (argc <= 1) {
		cout << "输入错误！输入-h查看帮助。" << endl;
		return 1;
	}

	//显示帮助
	if (!strcmp(argv[1], "-h")) { help(); return 0; }
	else if (!strcmp(argv[1], "-H")) { help(); return 0; }
	else if (!strcmp(argv[1], "--help")) { help(); return 0; }
	else if (!strcmp(argv[1], "-help")) { help(); return 0; }
	else if (!strcmp(argv[1], "?")) { help(); return 0; }

	std::string fileName1, fileName2;
	if (argc < 3) {
		cout << "输入错误！输入-h查看帮助。" << endl;
		return 1;
	}
	else if (argv[1][0] != '-') {
		// 省略 -c
		fileName1 = argv[1];
		fileName2 = argv[2];
	}

	SameCode sc;
	// 检测是否开启动态模式
	for (int a = 1; a < argc; a++) {
		//输入比较文件名
		if ((!strcmp(argv[a], "-d")) || (!strcmp(argv[a], "--dynamic")))
			sc.isStaticMode = false;
	}

	for (int a = 1; a < argc; a++) {
		//输入比较文件名
		if ((!strcmp(argv[a], "-c")) || (!strcmp(argv[a], "--compare"))) {
			if (a + 2 < argc) {
				fileName1 = argv[a + 1];
				fileName2 = argv[a + 2];
				a += 2;
			}
			else {
				cout << "输入错误！输入-h查看帮助。" << endl;
				return 1;
			}
		}
	}


	compare(sc, fileName1, fileName2);

	return 0;
	
#endif // TEST

}