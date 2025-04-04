######################################################################
# Automatically generated by qmake (3.1) Wed Apr 2 17:52:52 2025
######################################################################

TEMPLATE = app
TARGET = BibliothecaProcurator
INCLUDEPATH += .
QT += core widgets gui

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += src/graphics/CreateItemWidget.h \
           src/graphics/MainWindow.h \
           src/graphics/TopMenuWidget.h \
           src/json/JsonManager.h \
           src/logic/Anime.h \
           src/logic/Cd.h \
           src/logic/Film.h \
           src/logic/Libro.h \
           src/logic/Manga.h \
           src/logic/Media.h \
           src/logic/Series.h \
           src/logic/SerieTv.h
SOURCES += main.cpp \
           src/graphics/CreateItemWidget.cpp \
           src/graphics/MainWindow.cpp \
           src/graphics/TopMenuWidget.cpp \
           src/json/JsonManager.cpp \
           src/logic/Anime.cpp \
           src/logic/Cd.cpp \
           src/logic/Film.cpp \
           src/logic/Libro.cpp \
           src/logic/Manga.cpp \
           src/logic/Media.cpp \
           src/logic/Series.cpp \
           src/logic/SerieTv.cpp
