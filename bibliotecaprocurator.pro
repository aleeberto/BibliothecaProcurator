QT += core gui widgets

CONFIG += c++17
TEMPLATE = app
TARGET = my_project

# Percorsi di inclusione
INCLUDEPATH += src \
               src/app \
               src/logic \
               src/ui

# Sorgenti C++
SOURCES += \
    src/main.cpp \
    src/app/jsonService.cpp \
    src/logic/anime.cpp \
    src/logic/cartaceo.cpp \
    src/logic/cd.cpp \
    src/logic/film.cpp \
    src/logic/libro.cpp \
    src/logic/manga.cpp \
    src/logic/media.cpp \
    src/logic/series.cpp \
    src/logic/serieTv.cpp \
    src/ui/createItemWidget.cpp \
    src/ui/mainWindow.cpp \
    src/ui/topMenuWidget.cpp

# Header
HEADERS += \
    src/app/jsonService.h \
    src/logic/anime.h \
    src/logic/cartaceo.h \
    src/logic/cd.h \
    src/logic/film.h \
    src/logic/libro.h \
    src/logic/manga.h \
    src/logic/media.h \
    src/logic/series.h \
    src/logic/serieTv.h \
    src/ui/createItemWidget.h \
    src/ui/mainWindow.h \
    src/ui/topMenuWidget.h

# File .ui se ne hai (Qt Designer)
FORMS +=

# File risorse Qt (.qrc) se presenti
RESOURCES +=
