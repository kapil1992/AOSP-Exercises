#include "BnExample.h"

namespace android {
class Example : public BnExample
{
	int32_t exampleVal;
        ComplexData_t data;
public:
    Example(){ exampleVal = 25; }
    ~Example(){}

    int32_t getExample();
    void setExample(int32_t num);
    ComplexData_t* getDetails();
};
}
