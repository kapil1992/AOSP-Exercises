#include <binder/IServiceManager.h>
#include <stdio.h>
#include <cutils/log.h>
#include <sys/mman.h>

#include "IExample.h"

#define ASHMEM_BUFFER_SIZE 16

using namespace android;

int main(int argc, char** argv) {
    int num;
    sp<IServiceManager> smanager = defaultServiceManager(); 
    sp<IBinder> binder = smanager->getService(String16("Example")); 
    sp<IExample> example = interface_cast<IExample>(binder);
    /*printf("Please enter the value for Example : ");
    scanf("%d", &num);
    example->setExample(num);*/
    int testFd = example->getExample();
    ALOGD("Ashmem: testFd = %d\n", testFd); 
    void * ptr = mmap(NULL, ASHMEM_BUFFER_SIZE * sizeof(char), PROT_READ, 
                      MAP_SHARED, testFd, 0); 

    if (ptr != NULL) {
        ALOGI("Memory value: 0x%x", *((int *) ptr)); 
        munmap(ptr, ASHMEM_BUFFER_SIZE);
    } 
    return 0;
}


