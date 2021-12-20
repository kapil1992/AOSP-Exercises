#include <binder/IServiceManager.h>
#include <stdio.h>

#include "IExample.h"

using namespace android;

int main(int argc, char** argv) {
    int num;
    ComplexData_t data;
    sp<IServiceManager> smanager = defaultServiceManager(); 
    sp<IBinder> binder = smanager->getService(String16("Example")); 
    sp<IExample> example = interface_cast<IExample>(binder);
    printf("Please enter the value for Example : ");
    scanf("%d", &num);
    example->setExample(num);
    int testValue = example->getExample();
    printf("Test value: %d\n", testValue); 
    memcpy(&data, example->getDetails(), sizeof(data));
    printf("Name [%s] and Age [%d]\n", data.name, data.age); 
}


