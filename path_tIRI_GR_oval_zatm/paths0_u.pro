<QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



TEMPLATE	= app
CONFIG		+= qt warn_on thread release

TARGET          = path0s_gr
DEPENDPATH=../../include 
#gfortran
#LIBS            = ../iri_3d/iri2007/libiri2007.a -lgfortran
LIBS            = ../iri2012/libiri2012.a -lgfortran
#g77
#LIBS            = ../iri_3d/iri2007/libiri2007.a -lg2c
#INTERFACE_DECL_PATH=.
#DEFINES     = _POSIX GL
DEFINES     = GL  
#QMAKE_LFLAGS_WINDOWS = /NODEFAULTlIB:MSVCRT.LIB
QMAKE_CFLAGS_RELEASE = 
QMAKE_CXXFLAGS_RELEASE = 
QMAKE_CFLAGS_MT= 
QMAKE_CXXFLAGS_MT=
OBJECTS_DIR = ./obj
TRANSLATIONS = ./paths0gr_ru.ts
UI_DIR      = ./ui
FORMS = ./ui/path.ui


HEADERS		= paths.h \
                  ../splayn/spcub.h \
                  ../iri_3d/iri_3d_new.h \
                  ../draw/draw.h \
                  ../draw/draw2.h \
                  ../draw/drawbase.h \
                  ../draw/drawmembase.h \
                  ../draw/drawpoligonmemfull.h \
                  mainwindow.h 

SOURCES		= main.cpp \
                  mainpath0s.cpp \
                  mainwindow.cpp \
		  main__.c \
		  coords.cpp \
                  coors.cpp \
                  funcs.cpp \
                  infils.cpp \
                  inions.cpp \
                  ionos.cpp \
                  ltv.cpp \
                  magfis.cpp \
		  outtrs.cpp \
		  soluts.cpp \
		  sopr.cpp \
                  moda.cpp \
		  treks.cpp \
                  prion.cpp \
                  extern.cpp \
		  ../splayn/spcub.cpp \
		  ../splayn/progon.cpp \
		  ../iri_3d/eschar.cpp \
                  ../iri_3d/iri_3d_new.cpp \
                  ../draw/draw.cpp \
                  ../draw/draw2.cpp \
                  ../draw/grraz.cpp \
                  ../draw/grrazmem.cpp \
                  ../draw/drawpoligonmemfull.cpp \
                  ../draw/drawmembase.cpp \
                  ../draw/drawbase.cpp
                  
