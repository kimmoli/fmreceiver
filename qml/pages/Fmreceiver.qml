import QtQuick 2.0
import Sailfish.Silica 1.0
import fmreceiver.Fmtoh 1.0

Page
{
    id: page

    property bool seeking: true
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

            Label
            {
                id: freqLabel
                anchors.horizontalCenter: parent.horizontalCenter
                text: fmtoh.frequency
                color: Theme.primaryColor
                font.pixelSize: 100
                font.bold: true
            }

            Row
            {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width

                Button
                {
                    text: "<<"
                    width: parent.width/3
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

                Label
                {
                    text: "seek"
                }

                Button
                {
                    text: ">>"
                    width: parent.width/3
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


