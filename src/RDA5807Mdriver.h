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
    uint8_t RDA5807P_GetSigLvl();
    bool RDA5807P_ValidStop(int freq);
    void RDA5807P_SetMute(bool mute);
    void RDA5807P_SetVolumeLevel(uint8_t level);
    void RDA5807P_SetFreq( int16_t curf );

    int RDA5807P_decodeRDS();

    QByteArray radioText;
    QByteArray radioTextPositions;
    QByteArray stationName;
    QByteArray stationNamePositions;


private:
    unsigned char RDA5807MAddress;

    uint16_t vol;

    uint16_t gChipID;
    uint8_t RDA5807P_REGW[10];

    void setVolume();

    unsigned char OperationRDAFM_2w(unsigned char operation, unsigned char *data, int numBytes);

    bool RDA5807P_Intialization(void);
    void RDA5807P_PowerOffProc(void);

};

#endif // RDA5807MDriver_H
