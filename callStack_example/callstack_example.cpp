#include <utils/CallStack.h>
void function1();
void function2();
void function3();
void function4();
void function5();

using namespace android;

CallStack callstack;
int main() {
	function1();
	callstack.dump();
	return 0;
}

void function1() {
	function2();
}

void function2() {
	 function3();
}

void function3() {
	 function4();
}

void function4() {
	 function5();
}

void function5() {
	callstack.update();
}
