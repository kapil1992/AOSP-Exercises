#include <stdio.h>
#include <cutils/log.h>
#include "gdbexample_lib_1.h"

int main()
{

	int res1 = lib1_func1(5, 15, 25, 30);
	int res2 = lib1_func2(5, 15, 25, 30);
	int res3 = lib1_func3(5, 15, 25, 30);
	int res4 = lib1_func4(5, 15, 25, 30);
	
	return res1 + res2 + res3 + res4;
}
