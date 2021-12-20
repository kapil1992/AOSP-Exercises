#include "Example.h"
#include <cutils/log.h>
#include <cutils/ashmem.h>
#include <sys/mman.h>

#define ASHMEM_BUFFER_SIZE 16

namespace android {

int32_t Example::getExample() {
    ALOGD("GetExample value = %d\n", exampleVal);
    return getfd();
}

void Example::setExample(int32_t num) {
    ALOGD("SetExample value = %d\n", num);
    exampleVal = num;
}

Example::Example() {
       //! Create Ashmem region 
       fd = ashmem_create_region("Ashmem region name", 
                    ASHMEM_BUFFER_SIZE * sizeof(char));

       if(fd < 0) {
          ALOGE("Ashmem: Failed to create ashmem region\n");
          return ;
       } 

       ALOGD("Ashmem: Fd created = %d\n", fd);
       //! Set permissions 
       ashmem_set_prot_region(fd, PROT_READ | PROT_WRITE); 
 
       //! Map memory 
       ptr = mmap(NULL, ASHMEM_BUFFER_SIZE * sizeof(char), 
                      PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 
       memset(ptr, 0x0, ASHMEM_BUFFER_SIZE * sizeof(char)); 
 
       //! Write some data to memory 
       *((int *) ptr) = 0xCAFED00D; 
       
       //! Release memory 
       munmap(ptr, ASHMEM_BUFFER_SIZE); 
    }

Example::~Example() {
       ALOGD("Example Destructor\n");
       close(fd);
}

int32_t Example::getfd() {
    ALOGD("Ashmem: Example FD is = %d\n", fd);
    return fd;
}
}
