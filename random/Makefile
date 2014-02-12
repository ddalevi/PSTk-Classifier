# Lib/include section
#####################

# THESE ARE THE LIBS/INCLUDES USED BY THIS MODULE
# Info about the common includes
COMMONINCDIR = ../common

# THIS IS THE MODULE ITSELF
# Info about the signalnoise lib
RANLIBDIR = ../lib
RANLIBPFX = random
RANLIB = lib$(RANLIBPFX).a

# Let this section hold the sources
SRCS = \
Random.cpp \
RandomDistribution.cpp \
RandomSingleton.cpp

# Let this section hold the headers
HDRS = \
RandomDistribution.h \
Random.h \
RandomSingleton.h

# Let this section hold the objects
OBJS = \
RandomDistribution.o \
Random.o \
RandomSingleton.o

# Total includes
INCLUDES = -I$(COMMONINCDIR)

CCC     = g++
OPTFLAGS = -O2 
WARNINGFLAGS = -Wall
FLAGS = $(INCLUDES) $(OPTFLAGS) $(WARNINGFLAGS)


# The default action to be made with just 'make'

$(RANLIB): $(OBJS)
	ar crv $(RANLIB) $(OBJS)

install: $(RANLIB)
	cp -pf $(RANLIB) $(RANLIBDIR)

clean:
	rm -f $(OBJS) $(RANLIB) *~ *.bak

depend:
	makedepend -- $(FLAGS) -- $(SRCS)


# rules to make the different object files
.SUFFIXES: .cpp .C .cc .c .cxx .o

.cpp.o:
			$(CCC) $(FLAGS) -c $<

.cc.o:
			$(CCC) $(FLAGS) -c $<

.c.o:
			$(CC) $(FLAGS) -c $<

# DO NOT DELETE THIS LINE -- make depend depends on it.

