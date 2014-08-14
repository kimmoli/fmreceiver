/*
Copyright (c) 2014 kimmoli kimmo.lindholm@gmail.com @likimmo

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "fmtoh.h"
#include <QSettings>
#include <QCoreApplication>
#include <QThread>

Fmtoh::Fmtoh(QObject *parent) :
    QObject(parent)
{
    emit versionChanged();

    vddStateSet(false);
    vddStateSet(true);

    m_volume = 10;
    m_frequency = 9400;

    fmrx = new RDA5807MDriver(RDA5807M_ADDRESS);

}

QString Fmtoh::readVersion()
{
    return APPVERSION;
}


Fmtoh::~Fmtoh()
{
    delete fmrx;

    vddStateSet(false);
}


/*
 * Function to control TOH Vdd state
 */
void Fmtoh::vddStateSet(bool state)
{
    qDebug() << "TOH VDD:" << (state ? "on" : "off");

    int fd = open("/sys/devices/platform/reg-userspace-consumer.0/state", O_WRONLY);

    if (!(fd < 0))
    {
        if (write (fd, state ? "1" : "0", 1) != 1)
            qCritical() << "Failed to control VDD.";

        close(fd);
        return;
    }

    QThread::msleep(100);
}


void Fmtoh::powerOn()
{
    fmrx->RDA5807P_SetMute(false);
    fmrx->RDA5807P_SetVolumeLevel(m_volume);
    fmrx->RDA5807P_SetFreq(m_frequency);

    emit frequencyChanged();
    emit volumeChanged();
}

void Fmtoh::seek(QString dir)
{
    if (dir == "down")
    {
        m_frequency -= FREQ_STEP;

        if (m_frequency < FREQ_MIN)
            m_frequency = FREQ_MAX;
    }
    else if (dir == "up")
    {
        m_frequency += FREQ_STEP;

        if (m_frequency > FREQ_MAX)
            m_frequency = FREQ_MIN;
    }

    emit frequencyChanged();

    if (fmrx->RDA5807P_ValidStop(m_frequency))
        emit stationFound();
    else
        emit stationNotFound();
}

QString Fmtoh::readFrequency()
{
    return QString("%1 MHz").arg(QString::number(((double)m_frequency)/100.0, 'f', 1));
}

void Fmtoh::setVolume(int vol)
{
    m_volume = vol;
    fmrx->RDA5807P_SetVolumeLevel(m_volume);

    emit volumeChanged();
}



