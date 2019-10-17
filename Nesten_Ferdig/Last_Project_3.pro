TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Integration_loops.cpp \
        Laguerre.cpp \
        legendre.cpp \
        main.cpp \
        montecarlo.cpp \
        repulsion_function.cpp

HEADERS += \
    Integration_loops.h \
    Laguerre.h \
    legendre.h \
    montecarlo.h \
    repulsion_function.h
