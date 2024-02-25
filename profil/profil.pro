TEMPLATE	= app
CONFIG		+= qt warn_on thread release
#CONFIG		+= qt warn_on release

LIBS            = ../f2c/bcf2c.lib
#LIBS            = -lf2c
TARGET          = profil
DEPENDPATH=../../include 
#INTERFACE_DECL_PATH=.
DEFINES     = _POSIX GL
#DEFINES     = GL  
#QMAKE_LFLAGS_WINDOWS = /NODEFAULTlIB:MSVCRT.LIB
#QMAKE_CFLAGS_RELEASE = -LM
#QMAKE_CXXFLAGS_RELEASE = -LM
#QMAKE_CFLAGS_MT= 
#QMAKE_CXXFLAGS_MT=
#LANGUAGE	= C++
TRANSLATIONS = ./profil_ru.ts
MOC_DIR = ./moc
OBJECTS_DIR = ./obj
UI_DIR = ./ui

HEADERS		= mainwindow.h \
                  ../f2c/f2c.h \ 
                  ../iri_3d/iri_3d_new.h \
                  ../splayn/spcub.h \
                  ../draw/draw.h \
                  ../draw/drawbase.h \
                  ../draw/drawmem.h \
                  ../draw/drawmembase.h

SOURCES		= main.cpp \
                  mainwindow.cpp \
                  ../iri_3d/iri_3d_new.cpp \
		  ../splayn/spcub.cpp \
                  ../splayn/progon.cpp \
                  ../msis/msise90.cpp \
		  ../iri_3d/igrf.c \
		  ../iri_3d/iridreg.c \
                  ../iri_3d/irifun.c \
                  ../iri_3d/irisubne.c \
                  ../iri_3d/irisub.c \
                  ../iri_3d/iritecne.c \
		  ../iri_3d/cira.c \
		  ../iri_3d/eschar.cpp \
                  ../draw/drawmem.cpp \
                  ../draw/draw.cpp \
                  ../draw/grrazmem.cpp \
                  ../draw/grraz.cpp \
                  ../draw/drawmembase.cpp \
                  ../draw/drawbase.cpp
                  
		  
INTERFACES      = ./ui/profilwindow.ui \
                  ./ui/options.ui  
                  


