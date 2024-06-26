
LIB=../lib/libspherepack.a

UNAMES := $(shell uname -s)

ENFORCE_64_BIT_PRECISION = \
-fdefault-real-8 \
-fdefault-double-8 \
-fallow-argument-mismatch

#EXTERNAL_LIB_DIRECTORY = /usr/local/lib
EXTERNAL_LIB_DIRECTORY = /usr/local/lib64

BIN_DIRECTORY = /usr/local/bin

ifeq ($(UNAMES),Linux)

  PGI := $(shell pgf90 2>&1)

  ifeq ($(PGI),pgf90-Warning-No files to process)

    F90 := pgf90 -module ../lib -I../lib
    CPP := pgf90 -E

  else

    F90 := gfortran -O3 $(ENFORCE_64_BIT_PRECISION) -std=legacy
    CPP := gfortran -cpp

  endif

  MAKE := gmake
  AR := /usr/bin/ar

endif

ifeq ($(UNAMES),AIX)

  F90 := xlf -qmoddir=../lib -I../lib
  CPP := xlf -d -qnoobject
  MAKE := gmake
  AR := /usr/bin/ar

endif

ifeq ($(UNAMES),SunOS)

    AR := /usr/ccs/bin/ar
    F90 := /opt/SUNWspro/bin/f90 -moddir=../lib -I../lib
    CPP := /opt/SUNWspro/bin/f90 -F
    MAKE := /fs/local/bin/make

endif

ifeq ($(UNAMES),IRIX64)

    AR := /usr/bin/ar
    F90 := f90 -I../lib
    CPP := f90 -E
    MAKE := /usr/bin/make

endif

ifeq ($(UNAMES),Darwin)

    AR := /usr/bin/ar
    F90 := gfortran -O3 $(ENFORCE_64_BIT_PRECISION)
    CPP := gfortran -cpp
    MAKE := /usr/bin/make

endif
