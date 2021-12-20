#include "ImageDataServer.h"
#include <cutils/log.h>
#include <cutils/ashmem.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define ASHMEM_BUFFER_SIZE 1*1024*1024 

namespace android {

ImageDataServer::ImageDataServer() {
    count = 0;
    //! Create Ashmem region 
    ashmemFd = ashmem_create_region("Ashmem region name", ASHMEM_BUFFER_SIZE * sizeof(unsigned char));

    if(ashmemFd < 0) {
          ALOGE("Ashmem: Failed to create ashmem region\n");
          return ;
    }

    ALOGD("Ashmem: Fd created = %d\n", ashmemFd);
    //! Set permissions 
    ashmem_set_prot_region(ashmemFd, PROT_READ | PROT_WRITE);
}

ImageDataServer::~ImageDataServer() {
       ALOGD("ImageDataServer Destructor\n");
}

int32_t ImageDataServer::getAshmemFd() {
	ALOGD("getAshmemFd = [%d]\n", ashmemFd);
        return ashmemFd;
}

int32_t ImageDataServer::requestNextImage() {
    ALOGD("requestNextImage\n");
    char filepath[64] = {0};
    FILE *file;
    char *buffer;
    unsigned long fileLen;
    int num_read=0, i;
    count++;
    switch(count) {
	case 1: strcpy(filepath, "/data/images/image1.jpeg");
		break;

    	case 2: strcpy(filepath, "/data/images/image2.jpeg");
		break;

	case 3: strcpy(filepath, "/data/images/image3.jpeg");
	default:
		count = 0;
    }

    //Open file
    file = fopen(filepath, "rb");
    if (!file)
    {
        fprintf(stderr, "Unable to open file %s", filepath);
        return -1;
    }

    //Get file length
    fseek(file, 0, SEEK_END);
    fileLen=ftell(file);
    fseek(file, 0, SEEK_SET);

    //Allocate memory
    /*buffer=(char *)malloc(fileLen+1);
    memset(buffer, '\0', fileLen+1);
    if (!buffer)
    {
        fprintf(stderr, "Memory error!");
        fclose(file);
        return -1;
    }*/
    
    //! Map memory 
    ptr = (char*) mmap(NULL, ASHMEM_BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, ashmemFd, 0); 
    memset(ptr, 0, ASHMEM_BUFFER_SIZE);

    num_read = fread(ptr, 1, fileLen, file);

    ALOGD("fileLen: %lu num_read = %d filepath = %s", fileLen, num_read, filepath);
    ALOGD("\n========================================\n");
    ALOGD("\n            Source Buffer               \n");
    for (i = 0; i < 20 ; i++)
    	ALOGD("%02X", ptr[i]);
    ALOGD("\n========================================\n");
    //free(buffer);
    fclose(file);
    munmap(ptr, ASHMEM_BUFFER_SIZE);
    return fileLen;    
}

}
