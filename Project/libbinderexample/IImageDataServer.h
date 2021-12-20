#ifndef ANDROID_IEXAMPLE_H
#define ANDROID_IEXAMPLE_H

#include <binder/IInterface.h>

namespace android
{

class IImageDataServer : public IInterface
{
public:

    enum 
    {
        GET_ASHMEM_FD = IBinder::FIRST_CALL_TRANSACTION + 0,
        GET_IMAGE = IBinder::FIRST_CALL_TRANSACTION + 1,
    };

    virtual int32_t getAshmemFd() = 0;
    virtual int32_t requestNextImage() = 0;
    DECLARE_META_INTERFACE(ImageDataServer);
};

}

#endif

