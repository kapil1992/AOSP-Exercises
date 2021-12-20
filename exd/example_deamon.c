#define LOG_TAG "EXD" 
#include <cutils/log.h> 
#include <unistd.h> 
 
int main() 
{ 
    while(1) 
    { 
        ALOGD("TICK"); 
        sleep(5); //seconds 
    } 
    return 0; 
} 
