FOR       = gfortran
FORFLAGS   =
#FORFLAGS   = -Wall -W -g  -D_POSIX
LEXFLAGS = 
INCPATH  = 
LINK     = g++
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

SOURCES =     	iri2007/cira.for \
		iri2007/igrf.for \
		iri2007/iridreg.for \
		iri2007/irifun.for \
		iri2007/irisub.for \
		iri2007/iritec.for \
		iri2007/msise90.for

OBJECTS =     	cira.o \
		igrf.o \
		iridreg.o \
		irifun.o \
		irisub.o \
		iritec.o \
		msise90.o
                
                
TARGET_lib =	libiri2007.a


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

msise90.o: msise90.for