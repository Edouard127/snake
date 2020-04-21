TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp
HEADERS +=
QT += core
CONFIG += console
INCLUDEPATH += include
LIBS += -L$$PWD/lib -lmingw32 -mwindows -lSDL2main -lSDL2
CONFIG(debug, debug|release){
DESTDIR = $$PWD/debug
}
CONFIG(release, debug|release){
DESTDIR = $$PWD/release
}
win32{
WINDOWS_PWD = $$replace(PWD, /, \\)
WINDOWS_DESTDIR = $$replace(DESTDIR, /, \\)
QMAKE_POST_LINK += xcopy /Y $$WINDOWS_PWD\bin\SDL2.dll $$WINDOWS_PDW\
}
