NAME         = QtFFT
TARGET       = $${NAME}

QT           = core
QT          -= gui
CONFIG(static,static|shared) {
# static version does not support Qt Script now
QT          -= script
} else {
QT          += script
}
QT          += network
QT          += sql
QT          += QtCUDA
QT          += Essentials
QT          += QtGMP
QT          += QtGSL

load(qt_build_config)
load(qt_module)

INCLUDEPATH += $${PWD}/../../include/$${NAME}

HEADERS     += $${PWD}/../../include/$${NAME}/fftw3.h
HEADERS     += $${PWD}/../../include/$${NAME}/qtfft.h

SOURCES     += $${PWD}/nWavelet.cpp
SOURCES     += $${PWD}/nHankel.cpp
SOURCES     += $${PWD}/AbstractFFT.cpp
SOURCES     += $${PWD}/FFTW.cpp
SOURCES     += $${PWD}/GSLFFT.cpp
SOURCES     += $${PWD}/KissFFT.cpp
SOURCES     += $${PWD}/AccelerateFFT.cpp
SOURCES     += $${PWD}/CooleyFFT.cpp

OTHER_FILES += $${PWD}/../../include/$${NAME}/headers.pri

include ($${PWD}/../../doc/Qt/Qt.pri)

TRNAME       = $${NAME}
include ($${PWD}/../../Translations.pri)

win32 {
  CONFIG(debug,debug|release) {
    LIBS    += -lgslcblasd
    LIBS    += -lgsld
    LIBS    += -lfftw3-3
    LIBS    += -lfftw3f-3
    LIBS    += -lfftw3l-3
  } else {
    LIBS    += -lgslcblas
    LIBS    += -lgsl
    LIBS    += -lfftw3-3
    LIBS    += -lfftw3f-3
    LIBS    += -lfftw3l-3
  }
} else {
  CONFIG(debug,debug|release) {
    LIBS    += -lgslcblasd
    LIBS    += -lgsld
    LIBS    += -lfftw3
    LIBS    += -lfftw3f
    LIBS    += -lfftw3l
  } else {
    LIBS    += -lgslcblas
    LIBS    += -lgsl
    LIBS    += -lfftw3
    LIBS    += -lfftw3f
    LIBS    += -lfftw3l
  }
}
