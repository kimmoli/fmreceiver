import QtQuick 2.0
import Sailfish.Silica 1.0
import fmreceiver.Fmtoh 1.0

Page
{
    id: page

    property bool seeking: false
    property string seekDirection: ""

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

            }

            Slider
            {
                id: volumeSlider
                label: "Volume"
                value: fmtoh.volume
                valueText: value
                minimumValue: 0
                maximumValue: 15
                stepSize: 1
                width: parent.width - 2*Theme.paddingLarge
                anchors.horizontalCenter: parent.horizontalCenter
                onValueChanged: fmtoh.volume = value
            }


        }
    }

    Fmtoh
    {
        id: fmtoh
        Component.onCompleted: fmtoh.powerOn()

        onStationFound:
        {
            seeking = false;
        }
        onStationNotFound:
        {
            if (seeking)
                seekTimer.start()
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
}


