TEMPLATE	= app
CONFIG		= warn_on debug

HEADERS		= iri_3d_new.h \
                  ../splayn/spcub.h \

SOURCES		= main.cpp \
                  iri_3d_new.cpp \
		  ../splayn/spcub.cpp \
                  ../splayn/progon.cpp \
                  eschar.cpp \
                  ./msis/msise90.cpp \
		  ./iri2007/cira.cpp \
                  ./iri2007/igrf.cpp \
                  ./iri2007/iridreg.cpp \
                  ./iri2007/irifun.cpp \
                  ./iri2007/irisub.cpp \
                  ./iri2007/iritec.cpp

INTERFACES      = 
#LIBS            = -l ../f2c/vcf2c
LIBS            = ../f2c/libf2c.a
TARGET          = iri_3d
DEPENDPATH=../../include 
INTERFACE_DECL_PATH=.
TMAKE_CFLAGS=
TMAKE_CXXFLAGS= -fexceptions
DEFINES     = _POSIX