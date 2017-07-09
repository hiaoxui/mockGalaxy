TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    util.cpp \
    texture.cpp \
    text2D.cpp \
    tangentspace.cpp \
    sphere.cpp \
    space.cpp \
    ship.cpp \
    shader.cpp \
    planet.cpp \
    objloader.cpp \
    display.cpp \
    density.cpp \
    ddsvec.cpp \
    controls.cpp \
    body.cpp \
    backgroundloader.cpp


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += glfw3

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += glew

HEADERS += \
    util.h \
    texture.h \
    text2D.h \
    tangentspace.h \
    sphere.h \
    space.h \
    ship.h \
    shader.h \
    planet.h \
    objloader.h \
    density.h \
    ddsvec.h \
    controls.h \
    body.h \
    backgroundloader.h \
    display.h
