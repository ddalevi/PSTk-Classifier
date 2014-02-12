# Copyright (C) 2005 Daniel Dalevi
# Distributed under the GNU GENERAL PUBLIC LICENSE version 2

SRCS = Parameters.cpp \
       Classifier.cpp \
       FileHandler.cpp \
       main.cpp

HDRS = Parameters.h \
       Classifier.h 

OBJS = Parameters.o \
       Classifier.o \
       FileHandler.o \
       main.o   

# Common includes 
COMMONINCDIR = ../common

 
# GSLLIBRARYDIR = /usr/include/gsl

# A random singleton
RANDOMINCDIR = ../random

# The PST-tree
TREEINCDIR = ../trees

INCLUDES =  -I$(COMMONINCDIR) -I$(TREEINCDIR) -I$(RANDOMINCDIR)

LIBDIRS = -L../lib 

LIBS = -ltrees  -lrandom -lcommon 


APP = classifier
CCC	= g++
OPTFLAGS = -O9
CFLAGS = $(STATIC) $(OPTFLAGS)
FLAGS = $(OPTFLAGS) $(INCLUDES) 

$(APP):	$(OBJS)
	$(CCC) $(CFLAGS) -o $(APP) $(FLAGS) $(OBJS) $(LIBDIRS) $(LIBS) 



clean:
	/bin/rm -f $(APP) $(OBJS) *~ *.bak

.SUFFIXES: .cpp .C .cc .c .cxx .o

.cpp.o:
	$(CCC) $(FLAGS) -c $<

.cc.o:
	$(CCC) $(FLAGS) -c $<

.c.o:
	$(CC)  $(FLAGS) -c $<

depend:
	makedepend -- $(FLAGS) -- $(SRCS)

# DO NOT DELETE THIS LINE -- make depend depends on it.
