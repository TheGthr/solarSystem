# configuration Qt
QT       += core gui opengl widgets
TEMPLATE  = app

# ajout des libs au linker
win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib
    } else {
        LIBS     += -lopengl32 -lglu32
    }
}
unix {
	LIBS     += -lGL -lGLU
}


# nom de l'exe genere
TARGET 	  = TD3

# fichiers sources/headers/ressources
SOURCES += main.cpp myglwidget.cpp planet.cpp \
    trackball.cpp \
    stars.cpp
HEADERS += myglwidget.h planet.h \
    trackball.h \
    stars.h

RESOURCES += \
    ressources.qrc
