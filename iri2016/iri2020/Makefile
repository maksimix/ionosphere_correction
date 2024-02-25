#include ../make_inc
FOR       = gfortran
#FOR       = g77
FORFLAGS   =
#FORFLAGS   = -Wall -W -g  -D_POSIX
LEXFLAGS = 
INCPATH  = 
#LINK     = g++
LFLAGS   = 
AR       = ar cqs
TAR      = tar -cf
GZIP     = gzip -9f
COPY     = cp -f
COPY_FILE= $(COPY)
COPY_DIR = $(COPY) -r
INSTALL_FILE= $(COPY_FILE)
INSTALL_DIR = $(COPY_DIR)
DEL_FILE = rm -f
SYMLINK  = ln -sf
DEL_DIR  = rmdir
MOVE     = mv -f

####### Output directory

OBJECTS_DIR = ./

####### Files

SOURCES =     	iri2020/cira.for \
		iri2020/igrf.for \
		iri2020/iridreg.for \
		iri2020/irifun.for \
		iri2020/irisub.for \
		iri2020/iritec.for  \
		iri2020/iriflip.for  \
		iri2020/initial.for 
#		iri2020/msise90.for

OBJECTS =     	cira.o \
		igrf.o \
		iridreg.o \
		irifun.o \
		irisub.o \
		iritec.o \
		iriflip.o  \
		initial.o 
#		msise90.o
                
                
TARGET_lib =	libiri2020.a


####### Implicit rules

.SUFFIXES: .for .f .FOR .F

.for.o:
	$(FOR) -c $(FORFLAGS) $(INCPATH) -o $@ $<

.f.o:
	$(FOR) -c $(FORFLAGS) $(INCPATH) -o $@ $<

.FOR.o:
	$(FOR) -c $(FORFLAGS) $(INCPATH) -o $@ $<

.F.o:
	$(FOR) -c $(FORFLAGS) $(INCPATH) -o $@ $<

####### Build rules

all: lib


lib: $(TARGET_lib)

$(TARGET_lib): $(UICDECLS) $(OBJECTS) $(OBJMOC) 
	-rm -f $(TARGET_lib)
	$(AR) $(TARGET_lib) $(OBJECTS) $(OBJMOC)

	

clean:
	-rm -f $(OBJECTS) $(TARGET_lib)

	-rm -f *~ core

####### Compile


cira.o: cira.for 

igrf.o: igrf.for

iridreg.o: iridreg.for

irifun.o: irifun.for 

irisub.o: irisub.for 

iritec.o: iritec.for 

iriflip.o: iriflip.for

initial.o: initial.for 

#msise90.o: msise90.for