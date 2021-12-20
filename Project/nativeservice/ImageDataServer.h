#include "BnImageDataServer.h"

namespace android {
class ImageDataServer : public BnImageDataServer
{
        char* ptr;
        int32_t ashmemFd;
	int32_t count;
public:
    ImageDataServer(); 
    ~ImageDataServer();
    int32_t getAshmemFd();
    int32_t requestNextImage();
};
}
