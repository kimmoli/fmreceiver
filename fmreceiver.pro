#
# Project fmreceiver, FM Receiver TOH
#

TARGET = fmreceiver

CONFIG += sailfishapp

DEFINES += "APPVERSION=\\\"$${SPECVERSION}\\\""

message($${DEFINES})

SOURCES += src/fmreceiver.cpp \
	src/fmtoh.cpp \
    src/driverBase.cpp \
    src/RDA5807Mdriver.cpp
	
HEADERS += src/fmtoh.h \
    src/driverBase.h \
    src/RDA5807Mdriver.h

OTHER_FILES += qml/fmreceiver.qml \
    qml/cover/CoverPage.qml \
    qml/pages/Fmreceiver.qml \
    qml/pages/AboutPage.qml \
    rpm/fmreceiver.spec \
	fmreceiver.png \
    fmreceiver.desktop

