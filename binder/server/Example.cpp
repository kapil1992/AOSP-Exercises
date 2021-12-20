#include "Example.h"
#include <cutils/log.h>

namespace android {

int32_t Example::getExample() {
    ALOGD("GetExample value = %d\n", exampleVal);
    return exampleVal;
}

void Example::setExample(int32_t num) {
    ALOGD("SetExample value = %d\n", num);
    exampleVal = num;
}

ComplexData_t* Example::getDetails() {
    ALOGD("Get Details:");
    data.age = 17;
    strcpy(data.name, "Kapil");
    return &data;
}

}
