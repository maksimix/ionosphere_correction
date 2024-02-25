#TEMPLATE	= app
#CONFIG		+= qt warn_on thread release
#CONFIG		+= qt warn_on release
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt



#gfortran
#LIBS            = ../iri_3d/iri2007/libiri2007.a -lgfortran
LIBS            = ../iri2012/libiri2012.a -lgfortran
#g77
#LIBS            = ../iri_3d/iri2007/libiri2007.a -lg2c
TARGET          = path0s
DEPENDPATH=../../include 
#INTERFACE_DECL_PATH=.
#DEFINES     = _POSIX GL
#DEFINES     = GL  
#QMAKE_LFLAGS_WINDOWS = /NODEFAULTlIB:MSVCRT.LIB
QMAKE_LFLAGS += -fopenmp -O0 -march=native
QMAKE_CXXFLAGS += -fopenmp -O0 -march=native
#QMAKE_CFLAGS_RELEASE = 
#QMAKE_CXXFLAGS_RELEASE = 
#QMAKE_CFLAGS_MT= 
#QMAKE_CXXFLAGS_MT=
OBJECTS_DIR = ./.obj

INTERFACES      = 

HEADERS		= paths.h \
          ../splayn/spcub.h \
          ../trek/mytrek.h \
          ../iri_3d/iri_3d_new.h

SOURCES		= path0s.cpp \
          infils.cpp \
          inions.cpp \
		  outtrs.cpp \
		  sopr.cpp \
          moda.cpp \
          prion.cpp \
          extern.cpp \
          magfis.cpp \
		  ../trek/coords.cpp \
          ../trek/coors.cpp \
          ../trek/treks.cpp \
          ../trek/funcs.cpp \                  
          ../trek/soluts.cpp \
          ../trek/ionos.cpp \
          ../trek/ltv.cpp \
          ../trek/mytrek.cpp \
		  ../splayn/spcub.cpp \
		  ../splayn/progon.cpp \
		  ../iri_3d/eschar.cpp \
          ../iri_3d/iri_3d_new.cpp

