TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += "D:/SFML-2.5.1/include"
LIBS += -L"D:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}
SOURCES += \
        background.cpp \
        collision.cpp \
        game.cpp \
        main.cpp \
        new_enemies.cpp \
        platform.cpp \
        player.cpp \
        texture_functions.cpp

HEADERS += \
    background.h \
    collision.h \
    enum_classes.h \
    game.h \
    new_enemies.h \
    platform.h \
    player.h \
    texture_functions.h
