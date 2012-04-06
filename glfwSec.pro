TEMPLATE = app
CONFIG += console
CONFIG -= qt

LIBS += -lglfw -lGL -lGLU -lGLEW -lXrandr -lX11 -lpthread

SOURCES += main.cpp \
    renderer.cpp \
    glUtil.cpp

HEADERS += \
    renderer.h \
    glUtil.h

OTHER_FILES += \
    fragment.glsl \
    vertex.glsl

