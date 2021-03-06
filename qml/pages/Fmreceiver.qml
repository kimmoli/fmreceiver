import QtQuick 2.0
import Sailfish.Silica 1.0
import fmreceiver.Fmtoh 1.0

Page
{
    id: page

    property bool seeking: false
    property string seekDirection: ""

    property int rdsPacketCount: 0
    property bool rdsFetching : false

    SilicaFlickable
    {
        anchors.fill: parent

        PullDownMenu
        {
            MenuItem
            {
                text: "About..."
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"),
                                          { "version": fmtoh.version,
                                              "year": "2014",
                                              "name": "FM Receiver TOH",
                                              "imagelocation": "/usr/share/icons/hicolor/86x86/apps/fmreceiver.png"} )
            }
        }

        contentHeight: column.height

        Column
        {
            id: column

            width: page.width
            spacing: Theme.paddingLarge
            PageHeader
            {
                title: "FM Receiver"
            }

            Row
            {
                width: parent.width
                Label
                {
                    id: freqLabel
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width - seekButtons.width
                    horizontalAlignment: Text.AlignHCenter
                    text: fmtoh.frequency
                    color: Theme.primaryColor
                    font.pixelSize: 100
                    font.bold: true
                }
                Column
                {
                    id: seekButtons
                    width: 64
                    IconButton
                    {
                        icon.source: "image://theme/icon-m-up"
                        onClicked:
                        {
                            if (!seeking)
                            {
                                seeking = true
                                seekDirection = "up"
                                seekTimer.start()
                            }
                            else
                                seeking = false;
                        }
                    }
                    IconButton
                    {
                        icon.source: "image://theme/icon-m-down"
                        onClicked:
                        {
                            if (!seeking)
                            {
                                seeking = true
                                seekDirection = "down"
                                seekTimer.start()
                            }
                            else
                                seeking = false;
                        }
                    }
                }

            }

            Slider
            {
                id: volumeSlider
                label: "Volume"
                value: 1
                valueText: value
                minimumValue: 0
                maximumValue: 15
                stepSize: 1
                width: parent.width - 2*Theme.paddingLarge
                anchors.horizontalCenter: parent.horizontalCenter
                onValueChanged: fmtoh.setVolume(value)
            }
            Label
            {
                id: rssi
                anchors.horizontalCenter: parent.horizontalCenter
                text: "0"
            }
            Button
            {
                id: rdsButton
                text: "RDS"
                anchors.horizontalCenter: parent.horizontalCenter
                enabled: !rdsFetching
                onClicked:
                {
                    fmtoh.clearRDS()
                    rdsFetching = true;
                    rdsPacketCount = 32
                    rdsTimer.start()
                }
            }

            Label
            {
                id: stationName
                anchors.horizontalCenter: parent.horizontalCenter
                text: fmtoh.rdsStationName
            }
            Label
            {
                id: radioText
                anchors.horizontalCenter: parent.horizontalCenter
                text: fmtoh.rdsRadioText
            }
        }
    }

    Fmtoh
    {
        id: fmtoh
        Component.onCompleted:
        {
            fmtoh.powerOn()
            volumeSlider.value = fmtoh.getVolume()
        }

        onStationFound:
        {
            seeking = false;
        }
        onStationNotFound:
        {
            if (seeking)
                seekTimer.start()
        }
        onRdsCycleComplete:
        {
            if (rdsFetching)
                rdsTimer.start()
            if (--rdsPacketCount == 0)
                rdsFetching = false;
        }
        onRdsAllReceived:
        {
            rdsFetching = false
            rdsTimer.stop()
            rdsPacketCount = 0
        }
    }

    Timer
    {
        id: seekTimer
        running: false
        interval: 10
        repeat: false
        onTriggered:
        {
            fmtoh.seek(seekDirection)
        }
    }

    Timer
    {
        id: rdsTimer
        running: false
        interval: 50
        repeat: false
        onTriggered:
        {
            fmtoh.getRDS()
        }
    }

    Timer
    {
        id: signalStrength
        interval: 1000
        repeat: true
        running: true
        onTriggered:
        {
            if (!seeking)
                rssi.text = fmtoh.getSignalLevel()
        }
    }

}


