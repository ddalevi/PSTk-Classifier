# Copyright (C) 2005 Daniel Dalevi
# Distributed under the GNU GENERAL PUBLIC LICENSE version 2

INCLUDES = -I ../random 

LIBS = 

SRCS = GeneBankRecord.cpp \
       Fasta.cpp \
       RankCorrelation.cpp \
       SequenceGenerator.cpp \
       StringTokenizer.cpp \
       MyMath.cpp \
       StatisticalTables.cpp \
       Util.cpp

OBJS = GeneBankRecord.o \
       Fasta.o \
       RankCorrelation.o \
       SequenceGenerator.o \
       StringTokenizer.o \
       MyMath.o \
       StatisticalTables.o \
       Util.o

COMMONLIBPFX = common
COMMONLIB = lib$(COMMONLIBPFX).a
COMMONLIBDIR = ../lib


CCC	= g++
OPTFLAGS = -O2
CFLAGS = $(STATIC) $(MYDEBUG) $(OPTFLAGS)
FLAGS = $(MYDEBUG) $(OPTFLAGS) $(INCLUDES) 


$(COMMONLIB): $(OBJS)
	ar crv $(COMMONLIB) $(OBJS)

clean:
	/bin/rm -f $(COMMONLIB) $(COMMONLIB) $(OBJS) *~ *.bak

install: $(COMMONLIB)
	cp -pf $(COMMONLIB) $(COMMONLIBDIR)


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
