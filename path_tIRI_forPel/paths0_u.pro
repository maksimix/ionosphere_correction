TEMPLATE	= app
CONFIG		+= qt warn_on thread release
#CONFIG		+= qt warn_on release

#LIBS            = ../f2c/vcf2c.lib
#LIBS            = ../f2c/libf2c.a
#gfortran
#LIBS            = ../iri_3d/iri2007/libiri2007.a -lgfortran
LIBS            = ../iri2016/libiri2016.a -lgfortran
#g77
#LIBS            = ../iri_3d/iri2007/libiri2007.a -lg2c
TARGET          = path0s
DEPENDPATH=../../include 
#INTERFACE_DECL_PATH=.
#DEFINES     = _POSIX GL
#DEFINES     = GL  
QMAKE_LFLAGS_WINDOWS = /NODEFAULTlIB:MSVCRT.LIB
QMAKE_CFLAGS_RELEASE = 
QMAKE_CXXFLAGS_RELEASE = 
QMAKE_CFLAGS_MT= 
QMAKE_CXXFLAGS_MT=
OBJECTS_DIR = ./.obj

INTERFACES      = 


HEADERS		= paths.h \
                  ../splayn/spcub.h \
                  ../iri_4d/iri_4d.h

SOURCES		= path0s.cpp \
		  readDir.cpp \
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
		  ../iri_4d/eschar.cpp \
                  ../iri_4d/iri_4d.cpp \
                  ../iri2016/c/readJF.c

