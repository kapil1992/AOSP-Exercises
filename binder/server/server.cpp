#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>
#include <utils/String16.h>
#include <stdio.h>

#include "Example.h"

using namespace android;

int main(int argc, char** argv) {
    defaultServiceManager()->addService(String16("Example"), new Example());
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;
}

