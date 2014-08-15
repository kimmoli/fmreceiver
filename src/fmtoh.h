/*
Copyright (c) 2014 kimmoli kimmo.lindholm@gmail.com @likimmo

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef FMTOH_H
#define FMTOH_H
#include <QObject>
#include "RDA5807Mdriver.h"


#define FREQ_STEP 10
#define FREQ_MIN 8750
#define FREQ_MAX 10800

class Fmtoh : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString version READ readVersion NOTIFY versionChanged())
    Q_PROPERTY(QString frequency READ readFrequency NOTIFY frequencyChanged())

    Q_PROPERTY(QString rdsRadioText READ readRadioText NOTIFY rdsRadioTextChanged())
    Q_PROPERTY(QString rdsStationName READ readStationName NOTIFY rdsStationNameChanged())

public:
    explicit Fmtoh(QObject *parent = 0);
    ~Fmtoh();

    QString readVersion();

    QString readFrequency();

    Q_INVOKABLE int getVolume() { return m_volume; }
    Q_INVOKABLE void setVolume(int vol);

    Q_INVOKABLE void seek(QString dir);
    Q_INVOKABLE void powerOn();
    Q_INVOKABLE int getSignalLevel();

    Q_INVOKABLE void clearRDS();
    Q_INVOKABLE void getRDS();

    QString readRadioText() { return m_rdsRadioText; }
    QString readStationName() { return m_rdsStationName; }

signals:
    void versionChanged();
    void frequencyChanged();
    void stationFound();
    void stationNotFound();
    void rdsRadioTextChanged();
    void rdsStationNameChanged();
    void rdsCycleComplete();
    void rdsAllReceived();

private:
    void vddStateSet(bool state);

    RDA5807MDriver* fmrx;

    QString m_rdsRadioText;
    QString m_rdsStationName;

    int m_frequency;
    int m_volume;
};


#endif // FMTOH_H

