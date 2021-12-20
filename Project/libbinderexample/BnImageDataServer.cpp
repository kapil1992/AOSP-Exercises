#define LOG_NDEBUG 0
#define LOG_TAG "BnExample"

#include <cutils/log.h>
#include <binder/Parcel.h>
#include "BnImageDataServer.h"

using namespace android;

status_t BnImageDataServer::onTransact(uint32_t code, const Parcel& data,
        Parcel* reply, uint32_t flags __attribute__((unused)))
{
    ALOGV("%s enter: code = %d", __FUNCTION__, code);

    data.checkInterface(this);

    switch(code)
    {
        
        case GET_IMAGE:
        {
            int32_t size = requestNextImage();
            ALOGD("BnImageDataServer: size = [%d]\n", size);
            reply->writeNoException();
            reply->writeInt32(size);
            break;
        }
        case GET_ASHMEM_FD:
	{
             int32_t filedes = getAshmemFd();
             reply->writeNoException();
             reply->writeFileDescriptor(filedes);
             ALOGD("BnImageDataServer: Filedes = [%d]\n", filedes);
             break;
	}
    }

    ALOGV("%s exit", __FUNCTION__);
    return NO_ERROR;
}

