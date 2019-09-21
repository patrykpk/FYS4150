TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        initializematrix.cpp \
        jacobi_method.cpp \
        main.cpp

INCLUDEPATH += C:\Users\dorki\Desktop\armadillo-9.600.6\include

INCLUDEPATH += $$PWD/../armadillo-9.600.6/examples/lib_win64
DEPENDPATH += $$PWD/../armadillo-9.600.6/examples/lib_win64

LIBS += \
    -LC:\Users\dorki\Desktop\armadillo-9.600.6\examples\lib_win64 \
    -llapack_win64_MT \
    -lblas_win64_MT

HEADERS += \
    initializematrix.h \
    jacobi_method.h
