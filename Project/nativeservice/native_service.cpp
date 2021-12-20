#include <cutils/log.h> 
#include <unistd.h> 
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/String16.h>

#include "ImageDataServer.h"

using namespace android;

int main() 
{
    ALOGD("============================================================================\n");
    ALOGD("====================== NativeGallary Service Started =======================\n");
    ALOGD("============================================================================\n");
    defaultServiceManager()->addService(String16("ImageDataServer"), new ImageDataServer());
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0; 
} 
