#include <cutils/properties.h> 
#include <cutils/log.h>
#include <stdio.h>

#define TAG "SystemPropertyRead"

int main() {
	const char key[] = "rtrk.android";
	char value[8] = {0};
	if (property_set(key, "RTRK") > 0) {
	   ALOGE(TAG, "Failed to set property\n");
	   return -1;
	} else printf ("property set successful\n");

	if (property_get(key, value, "") == 0) {
	    ALOGE(TAG, "Failed to read property\n");
	    return -1;
	} else printf("property read successful value = [%s]\n", value); 
        return 0;
}
