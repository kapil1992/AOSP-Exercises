#include <stdio.h> 
#include <libhellostatic.h> 
#include <libhelloshared.h> 
 
int main() 
{ 
    printf("Hello world\n");
    hello_static(); 
    hello_shared(); 
    return 0; 
}
