#ifndef RDA5807MDRIVER_H
#define RDA5807MDRIVER_H
#include "driverBase.h"

/*
 * I2C address of RDA5807M on FM TOH
 */
#define RDA5807M_ADDRESS 0x10


typedef unsigned char           uint8_t;
typedef unsigned short int      uint16_t;
typedef short int               int16_t;

class RDA5807MDriver : public DriverBase
{
    Q_OBJECT
public:
    explicit RDA5807MDriver(unsigned char address);
    ~RDA5807MDriver();

    void init();
    uint8_t RDA5807P_GetSigLvl( int16_t curf );
    void fmSeek();

private:
    unsigned char RDA5807MAddress;

    int16_t freq;
    uint16_t vol;

    uint16_t gChipID;
    uint8_t RDA5807P_REGW[10];

    void setVolume();

    unsigned char OperationRDAFM_2w(unsigned char operation, unsigned char *data, int numBytes);

    void RDA5807P_PowerOffProc(void);

    void RDA5807P_SetMute(bool mute);
    uint16_t RDA5807P_FreqToChan(uint16_t frequency);
    void RDA5807P_SetFreq( int16_t curf );
    bool RDA5807P_ValidStop(int freq);

    void RDA5807P_SetVolumeLevel(uint8_t level);
    bool RDA5807P_Intialization(void);
    uint16_t RDA5807P_ChanToFreq(uint16_t chan);



};

#endif // RDA5807MDriver_H
