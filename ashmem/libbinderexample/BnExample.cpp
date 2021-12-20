#define LOG_NDEBUG 0
#define LOG_TAG "BnExample"

#include <cutils/log.h>
#include <binder/Parcel.h>

#include "BnExample.h"

using namespace android;

status_t BnExample::onTransact(uint32_t code, const Parcel& data,
        Parcel* reply, uint32_t flags __attribute__((unused)))
{
    ALOGV("%s enter: code = %d", __FUNCTION__, code);

    data.checkInterface(this);

    switch(code)
    {
        
        case GET_EXAMPLE:
        {
            int32_t example = getExample();
            ALOGD("onTransact: example val = %d\n", example);
            reply->writeNoException();
            reply->writeFileDescriptor(example);
            break;
        }
	case SET_EXAMPLE:
	{
	    int32_t updateVal = data.readInt32();
	    setExample(updateVal);
	}
    }

    ALOGV("%s exit", __FUNCTION__);
    return NO_ERROR;
}

