#ifndef RDA5807MDRIVER_H
#define RDA5807MDRIVER_H
#include "driverBase.h"

/*
 * I2C address of RDA5807M on FM TOH
 */
#define RDA5807M_ADDRESS 0x10



class RDA5807MDriver : public DriverBase
{
    Q_OBJECT
public:
    explicit RDA5807MDriver(unsigned char address);
    ~RDA5807MDriver();

    void init();

private:
    unsigned char RDA5807MAddress;


};

#endif // RDA5807MDriver_H
