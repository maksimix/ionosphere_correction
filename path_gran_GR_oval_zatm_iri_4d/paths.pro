TEMPLATE	= app
CONFIG		+= qt warn_on thread release
#CONFIG		+= qt warn_on release

LIBS            = ../f2c/vcf2c.lib
#LIBS            = ../f2c/libf2c.a
TARGET          = paths_gr
DEPENDPATH=../../include 
#INTERFACE_DECL_PATH=.
#DEFINES     = _POSIX GL
DEFINES     = GL  
QMAKE_LFLAGS_WINDOWS = /NODEFAULTlIB:MSVCRT.LIB
QMAKE_CFLAGS_RELEASE = -ML
QMAKE_CXXFLAGS_RELEASE = -ML
QMAKE_CFLAGS_MT= 
QMAKE_CXXFLAGS_MT=
OBJECTS_DIR = ./.obj
TRANSLATIONS = ./pathsgr_ru.ts


HEADERS		= paths.h \
                  ../splayn/spcub.h \
                  ../iri_3d/iri_3d.h \
                  ../f2c/f2c.h \
                  ../draw/draw.h \
                  ../draw/drawbase.h \
                  ../draw/drawmem.h \
                  ../draw/drawmembase.h \
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
		  ../iri_3d/igrf.c \
		  ../iri_3d/iridreg.c \
                  ../iri_3d/irifun.c \
                  ../iri_3d/irine.c \
                  ../iri_3d/irisub.c \
                  ../iri_3d/iritecne.c \
		  ../iri_3d/cira.c \
		  ../iri_3d/eschar.cpp \
                  ../iri_3d/iri_3d.cpp \
		  ../splayn/spcub.cpp \
		  ../splayn/progon.cpp \
                  ../msis/msise90.c \                                    
                  ../draw/drawmem.cpp \
                  ../draw/draw.cpp \
                  ../draw/grrazmem.cpp \
                  ../draw/grraz.cpp \
                  ../draw/drawmembase.cpp \
                  ../draw/drawbase.cpp
                  
		  
INTERFACES      = ./.ui/path.ui
