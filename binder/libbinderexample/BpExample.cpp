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
    int32_t example;

    ALOGV("%s enter", __FUNCTION__);

    data.writeInterfaceToken(IExample::getInterfaceDescriptor());
    
    remote()->transact(GET_EXAMPLE, data, &reply);

    reply.readInt32();
    reply.readInt32(&example);    

    ALOGV("%s exit", __FUNCTION__);
    return example;
}

void BpExample::setExample(int32_t num)
{
    Parcel data, reply;

    ALOGV("%s enter", __FUNCTION__);

    data.writeInterfaceToken(IExample::getInterfaceDescriptor());
    data.writeInt32(num); 
    
    remote()->transact(SET_EXAMPLE, data, &reply);

    ALOGV("%s exit", __FUNCTION__);
}

ComplexData_t* BpExample::getDetails() {
	Parcel data, reply;
	ComplexData_t cmplxData;
	ALOGV("%s enter", __FUNCTION__);

        data.writeInterfaceToken(IExample::getInterfaceDescriptor());

        remote()->transact(GET_PERSON, data, &reply);

       reply.readExceptionCode();
       reply.read(&cmplxData, sizeof(cmplxData)); 
       
       ALOGD("Name [%s] and Age [%d]\n", cmplxData.name, cmplxData.age);

       ALOGV("%s exit", __FUNCTION__);
       return &cmplxData;
}
