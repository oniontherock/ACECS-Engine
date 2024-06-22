
#include <set>
#include <iostream>

int main() {

	struct Test {
		int testVal;
	};

	Test test1 = Test();
	test1.testVal = 0;
	Test test2 = Test();
	test2.testVal = 0;

	std::set<Test> set;

	set.insert(test1);


	return 0;
}
