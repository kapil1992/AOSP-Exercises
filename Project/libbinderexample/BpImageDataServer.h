#include "IImageDataServer.h"

namespace android
{

class BpImageDataServer : public BpInterface<IImageDataServer>
{

public:

    BpImageDataServer(const sp<IBinder>& impl);

    virtual int32_t getAshmemFd();
    virtual int32_t requestNextImage();
};

}

