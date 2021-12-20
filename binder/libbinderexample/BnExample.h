#include "IExample.h"

namespace android
{

class BnExample : public BnInterface<IExample>
{
      ComplexData_t* myData;
public:

    virtual status_t onTransact(uint32_t code, const Parcel& data,
            Parcel* reply, uint32_t flags = 0);

};

}

