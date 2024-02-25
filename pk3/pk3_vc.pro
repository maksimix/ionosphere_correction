TEMPLATE	= app
CONFIG		+= qt warn_on thread release
#CONFIG		+= qt warn_on release

LIBS            = ../f2c/vcf2c.lib
#LIBS            = ../f2c/bcf2c.lib
#LIBS            = ../f2c/libf2c.a
TARGET          = pk3_vc
DEPENDPATH=../../include 
#INTERFACE_DECL_PATH=.
#DEFINES     = _POSIX GL
#DEFINES     = GL  
QMAKE_LFLAGS_WINDOWS = /NODEFAULTlIB:MSVCRT.LIB
QMAKE_CFLAGS_RELEASE =  -ML
QMAKE_CXXFLAGS_RELEASE =  -ML
QMAKE_CFLAGS_MT= 
QMAKE_CXXFLAGS_MT=
OBJECTS_DIR = ./obj


HEADERS		= paths.h \
                  ../splayn/spcub.h \
                  ../iri_3d/iri_3d_new.h \
                  ../f2c/f2c.h

SOURCES		= paths.cpp \
		  pk3_modul.cpp \
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
                  solt.cpp \
                  solta.cpp \
                  mpchs.cpp \
                  extern.cpp \
                  ../iri_3d/iri_3d_new.cpp \
		  ../splayn/spcub.cpp \
                  ../splayn/progon.cpp \
                  ../msis/msise90.cpp \
		  ../iri_3d/igrf.cpp \
		  ../iri_3d/iridreg.cpp \
                  ../iri_3d/irifun.cpp \
                  ../iri_3d/irisub.cpp \
                  ../iri_3d/iritec.cpp \
		  ../iri_3d/cira.cpp \
		  ../iri_3d/eschar.cpp


