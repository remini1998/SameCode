#include <iostream>
#include "SameCode.h"
#define TEST

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

int main(int argc, char* argv[]) {
#ifdef TEST
	return test();
#else

#endif // TEST

}