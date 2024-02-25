TEMPLATE    = app
CONFIG      += qt warn_on thread debug
#CONFIG     += qt warn_on release

#LIBS            = ../f2c/vcf2c.lib
#LIBS            = ../f2c/libf2c.a
#gfortran
#LIBS            = ../iri_3d/iri2007/libiri2007.a -lgfortran
LIBS            = ../iri2012/libiri2012.a -lgfortran -lpthread -lgomp 
#g77
#LIBS            = ../iri_3d/iri2007/libiri2007.a -lg2c
TARGET          = paths
DEPENDPATH=../../include 
#INTERFACE_DECL_PATH=.
#DEFINES     = _POSIX GL
#DEFINES     = GL  
QMAKE_LFLAGS += -fopenmp -O0 -march=native
QMAKE_CXXFLAGS += -fopenmp -O0 -march=native
#QMAKE_LFLAGS += -O0 -march=native
#QMAKE_CXXFLAGS += -O0 -march=native
OBJECTS_DIR = ./.obj



HEADERS     = paths.h \
                  ../splayn/spcub.h \
                  ../iri_3d/iri_3d_new.h \
                   mysolt.h \
                  ../trek/mytrek.h

SOURCES     = paths.cpp \
                  infils.cpp \
                  inions.cpp \
                  magfis.cpp \
          outtrs.cpp \
                  solt.cpp \
                  moda.cpp \
                  soltA.cpp \
                  ssno.cpp \
                  grss.cpp \
                  wr_fil.cpp \
                  init_fil.cpp \
                  shell.cpp \
                  prion.cpp \
                  mpchs.cpp \
                  extern.cpp \
          ../antenn_omp/polar.cpp \
          ../antenn_omp/trant.cpp \
          ../antenn_omp/si.cpp \
          ../antenn_omp/resist.cpp \
          ../antenn_omp/rerth.cpp \
          ../antenn_omp/recant.cpp \
          ../antenn_omp/rebeam.cpp \
          ../antenn_omp/loop.cpp \
          ../antenn_omp/get_ant.cpp \
          ../antenn_omp/fm.cpp \
          ../antenn_omp/ci.cpp \
          ../antenn_omp/ellips.cpp \
          ../antenn_omp/dipole.cpp \
          ../antenn_omp/bs.cpp \
          ../antenn_omp/beam.cpp \
          ../iri_3d/eschar.cpp \
          ../iri_3d/iri_3d_new.cpp \
          ../splayn/spcub.cpp \
          ../splayn/progon.cpp \
    ../trek/coords.cpp \
    ../trek/coors.cpp \
    ../trek/funcs.cpp \
    ../trek/ionos.cpp \
    ../trek/ltv.cpp \
    ../trek/mytrek.cpp \
    ../trek/soluts.cpp \
    ../trek/sopr.cpp \
    ../trek/treks.cpp \
    ../trek/ltv_i.cpp
                  
          
INTERFACES      = 

OTHER_FILES +=
