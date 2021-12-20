#include <binder/IServiceManager.h>
#include <stdio.h>
#include <cutils/log.h>
#include <cutils/ashmem.h>
#include <sys/mman.h>

#include "IImageDataServer.h"
#include "native_binder_ashmem.h"

#define ASHMEM_BUFFER_SIZE 8*1024
using namespace android;
int fd, imageSize;
sp<IImageDataServer> example;

void  AshmemInit() {
    sp<IServiceManager> smanager = defaultServiceManager(); 
    sp<IBinder> binder = smanager->getService(String16("ImageDataServer")); 
    example = interface_cast<IImageDataServer>(binder);

    fd = example->getAshmemFd(); 
}

char* getImageData() {
        imageSize = example->requestNextImage();
	char* buf = (char*)malloc(imageSize);
       //! Map memory 
       char *ptr = (char*)mmap(NULL, ASHMEM_BUFFER_SIZE * sizeof(char), 
                      PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
       memcpy(buf, ptr, imageSize); 
       for (int i = 0; i < 10; i++)
	    ALOGD(" 0x%2x ", buf[i]);
       munmap(ptr, ASHMEM_BUFFER_SIZE);
       return buf; 
}

JNIEXPORT jbyteArray JNICALL Java_com_example_nativegallery_NativeAshmemBinder_getImageData(JNIEnv *env, jclass cls) {
	jbyte bArray[ASHMEM_BUFFER_SIZE];
	char *buf = getImageData();
        int i = 0;
	for (i = 0; i < imageSize; i++)	
	     bArray[i] = buf[i];
	jbyteArray ret = env->NewByteArray(imageSize);
	env->SetByteArrayRegion (ret, 0, imageSize, bArray);
	free(buf);
        return ret;
}

JNIEXPORT void JNICALL Java_com_example_nativegallery_NativeAshmemBinder_AshmemInit(JNIEnv *env, jclass cls) {
	AshmemInit();
}
