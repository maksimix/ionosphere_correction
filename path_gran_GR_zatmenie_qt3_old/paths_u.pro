TEMPLATE	= app
CONFIG		+= qt warn_on thread release

TARGET          = paths_gr
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
TRANSLATIONS = ./pathsgr_ru.ts
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
                  ../iri_3d/iri_3d_new.h \
                  mainwindow.h \

SOURCES		= main.cpp \
                  mainwindow.cpp \
                  mainpaths.cpp \
#		  main__.c \
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
                  solt.cpp \
		  sopr.cpp \
		  treks.cpp \
                  moda.cpp \
                  soltA.cpp \
                  ssno.cpp \
                  grss.cpp \
                  wr_fil.cpp \
                  shell.cpp \
                  prion.cpp \
                  mpchs.cpp \
                  extern.cpp \
		  ../antenn/polar.cpp \
		  ../antenn/trant.cpp \
		  ../antenn/si.cpp \
		  ../antenn/resist.cpp \
		  ../antenn/rerth.cpp \
		  ../antenn/recant.cpp \
		  ../antenn/rebeam.cpp \
		  ../antenn/loop.cpp \
		  ../antenn/get_ant.cpp \
		  ../antenn/fm.cpp \
		  ../antenn/ci.cpp \
		  ../antenn/ellips.cpp \
		  ../antenn/dipole.cpp \
		  ../antenn/bs.cpp \
		  ../antenn/beam.cpp \
		  ../iri_3d/eschar.cpp \
                  ../iri_3d/iri_3d_new.cpp \
		  ../splayn/spcub.cpp \
		  ../splayn/progon.cpp \
                  ../draw/draw.cpp \
                  ../draw/draw2.cpp \
                  ../draw/grraz.cpp \
                  ../draw/grrazmem.cpp \
                  ../draw/drawpoligonmemfull.cpp \
                  ../draw/drawmembase.cpp \
                  ../draw/drawbase.cpp
                  
		  

