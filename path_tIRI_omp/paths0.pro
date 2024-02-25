TEMPLATE	= app
CONFIG		+= qt warn_on thread release
#CONFIG		+= qt warn_on release

LIBS            = ../f2c/vcf2c.lib
#LIBS            = ../f2c/libf2c.a
TARGET          = path0s
DEPENDPATH=../../include 
#INTERFACE_DECL_PATH=.
#DEFINES     = _POSIX GL
#DEFINES     = GL  
QMAKE_LFLAGS_WINDOWS = /NODEFAULTlIB:MSVCRT.LIB
QMAKE_CFLAGS_RELEASE =  -ML
QMAKE_CXXFLAGS_RELEASE =  -ML
QMAKE_CFLAGS_MT= 
QMAKE_CXXFLAGS_MT=
OBJECTS_DIR = ./.obj


HEADERS		= paths.h \
                  ../splayn/spcub.h \
                  ../iri_3d/iri_3d.h \
                  ../f2c/f2c.h

SOURCES		= path0s.cpp \
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
		  ../splayn/spcub.cpp \
		  ../splayn/progon.cpp \
		  ../iri_3d/igrf.c \
		  ../iri_3d/iridreg.c \
                  ../iri_3d/irifun.c \
                  ../iri_3d/irine.c \
                  ../iri_3d/irisub.c \
                  ../iri_3d/iritecne.c \
		  ../iri_3d/cira.c \
		  ../iri_3d/eschar.cpp \
                  ../iri_3d/iri_3d.cpp \
                  ../msis/msise90.c \

