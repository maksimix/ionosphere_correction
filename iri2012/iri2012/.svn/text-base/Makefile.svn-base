FOR       = gfortran
FORFLAGS   =
#FORFLAGS   = -Wall -W -g  -D_POSIX
LEXFLAGS = 
INCPATH  = 
LINK     = g++
LFLAGS   = 
LIBS     = $(SUBLIBS) -L/usr/lib64/ 
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

SOURCES =     	iri2012/cira.for \
		iri2012/igrf.for \
		iri2012/iridreg.for \
		iri2012/irifun.for \
		iri2012/irisub.for \
		iri2012/iritec.for \
		iri2012/msise90.for

OBJECTS =     	cira.o \
		igrf.o \
		iridreg.o \
		irifun.o \
		irisub.o \
		iritec.o \
		msise90.o
                
                
#OBJECTS_lib =	$(OBJECTS)

INTERFACES =	
UICDECLS =	
UICIMPLS =	
SRCMOC	=	
OBJMOC	=	
DIST	=	

TARGET_lib =	libiri2012.a

INTERFACE_DECL_PATH = .



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


dist:
	$(TAR) iri2012.tar Makefile $(SOURCES) $(HEADERS) $(INTERFACES) $(DIST)
	$(GZIP) iri2012.tar

lib: $(TARGET_lib)

$(TARGET_lib): $(UICDECLS) $(OBJECTS) $(OBJMOC) 
	-rm -f $(TARGET_lib)
	$(AR) $(TARGET_lib) $(OBJECTS) $(OBJMOC)

	

clean:
	-rm -f $(OBJMOC) $(SRCMOC) $(UICIMPLS) $(UICDECLS)
	-rm -f $(OBJECTS) $(TARGET_lib)

	-rm -f *~ core

####### Compile


cira.o: cira.for 

igrf.o: igrf.for

iridreg.o: iridreg.for

irifun.o: irifun.for 

irisub.o: irisub.for 

iritec.o: iritec.for 

