#define LOG_NDEBUG 0
#define LOG_TAG "BpImageDataServer"

#include <cutils/log.h>
#include <binder/Parcel.h>

#include "BpImageDataServer.h"

using namespace android;


BpImageDataServer::BpImageDataServer(const sp<IBinder>& impl) :
	BpInterface<IImageDataServer>(impl)
{

}

int32_t BpImageDataServer::getAshmemFd()
{
    Parcel data, reply;
    int32_t filedes;

    ALOGV("%s enter ", __FUNCTION__);

    data.writeInterfaceToken(IImageDataServer::getInterfaceDescriptor());
    remote()->transact(GET_ASHMEM_FD, data, &reply);

    reply.readInt32();
    int32_t fd = dup(reply.readFileDescriptor());
    
    ALOGD("BpImageDataServer: filedes = [%d]\n", fd);
    ALOGV("%s exit", __FUNCTION__);
    return fd;
}

int32_t BpImageDataServer::requestNextImage()
{
    Parcel data, reply;
    int32_t imgSize;

    ALOGV("%s enter", __FUNCTION__);

    data.writeInterfaceToken(IImageDataServer::getInterfaceDescriptor());
    
    remote()->transact(GET_IMAGE, data, &reply);

    reply.readInt32();
    reply.readInt32(&imgSize);    

    ALOGV("%s exit", __FUNCTION__);
    return imgSize;
}
