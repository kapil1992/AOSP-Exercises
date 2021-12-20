#include "gdbexample_lib_3.h"

int lib3_func1(int value1, int value2, int value3, int value4)
{
	int tmp1 = 0, tmp2 = 0;
	if (value1 != (value4 - value3))
		tmp1 = value2 / (value1 - (value4 - value3));
	tmp2 = value3 * value4;
	return tmp1 * tmp2;
}

int lib3_func2(int value1, int value2, int value3, int value4)
{
	int tmp1 = 0, tmp2 = 0;
	tmp1 = value1 + value2 + 2*value1;
	tmp2 = value3 + value4 + 2*value1;
	return tmp1 + tmp2;
}

int lib3_func3(int value1, int value2, int value3, int value4)
{
	float tmp = 0.0f;
	for (int i = 0; i < value3; i++){
		tmp += (value1--)*(value2--)*(value4--);
	}
	return (int)tmp;
}

int lib3_func4(int value1, int value2, int value3, int value4)
{
	float tmp = 0.0f;
	for (int i = 0; i < value3; i++){
		tmp += value2/(value4--);
	}
	return (int)tmp;
}
