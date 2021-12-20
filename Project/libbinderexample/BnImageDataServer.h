#include "IImageDataServer.h"

namespace android
{

class BnImageDataServer : public BnInterface<IImageDataServer>
{
public:

    virtual status_t onTransact(uint32_t code, const Parcel& data,
            Parcel* reply, uint32_t flags = 0);

};

}

