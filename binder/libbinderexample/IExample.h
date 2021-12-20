#ifndef ANDROID_IEXAMPLE_H
#define ANDROID_IEXAMPLE_H

#include <binder/IInterface.h>
#include "ComplexData.h"

namespace android
{

class IExample : public IInterface
{
public:

    enum 
    {
        GET_EXAMPLE = IBinder::FIRST_CALL_TRANSACTION + 0,
        SET_EXAMPLE = IBinder::FIRST_CALL_TRANSACTION + 1,
        GET_PERSON = IBinder::FIRST_CALL_TRANSACTION + 2,
    };

    virtual int32_t getExample() = 0;
    virtual void setExample(int32_t num) = 0;
    virtual ComplexData_t* getDetails() = 0; 
    DECLARE_META_INTERFACE(Example);
};

}

#endif

