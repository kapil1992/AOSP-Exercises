#include "BnExample.h"

namespace android {
class Example : public BnExample
{
	int32_t exampleVal;
        int32_t fd;
        void *ptr;
public:
    Example(); 
    ~Example();
    int32_t getfd();
    int32_t getExample();
    void setExample(int32_t num);
};
}
