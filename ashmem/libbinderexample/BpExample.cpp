#define LOG_NDEBUG 0
#define LOG_TAG "BpExample"

#include <cutils/log.h>
#include <binder/Parcel.h>

#include "BpExample.h"

using namespace android;


BpExample::BpExample(const sp<IBinder>& impl) :
	BpInterface<IExample>(impl)
{

}

int32_t BpExample::getExample()
{
    Parcel data, reply;
    int example;

    ALOGV("%s enter", __FUNCTION__);

    data.writeInterfaceToken(IExample::getInterfaceDescriptor());
    
    remote()->transact(GET_EXAMPLE, data, &reply);

    reply.readExceptionCode();
    example = dup(reply.readFileDescriptor());    

    ALOGV("%s exit example = %d\n", __FUNCTION__, example);
    return example;
}

void BpExample::setExample(int32_t num)
{
    Parcel data, reply;

    ALOGV("%s enter", __FUNCTION__);

    data.writeInterfaceToken(IExample::getInterfaceDescriptor());
    data.writeFileDescriptor(num); 
    
    remote()->transact(SET_EXAMPLE, data, &reply);

    ALOGV("%s exit", __FUNCTION__);
}
