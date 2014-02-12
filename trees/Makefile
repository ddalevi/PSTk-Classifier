INCLUDES = -I../random \
           -I../common 

LIBS = -lcommon -lrandom  

LIBDIRS = -L../lib 

SRCS = Node.cpp \
       Tree.cpp \
       PstTree.cpp \
       FixedTree.cpp \
       NaiveTree.cpp \
       TreeFactory.cpp \
       TreeModifier.cpp \
       PSModifier.cpp \
       KLModifier.cpp 

OBJS = Node.o \
       Tree.o \
       PstTree.o \
       FixedTree.o \
       NaiveTree.o \
       TreeFactory.o \
       TreeModifier.o \
       PSModifier.o \
       KLModifier.o 



PSTTREELIBPFX = trees
PSTTREELIB = lib$(PSTTREELIBPFX).a
PSTTREELIBDIR = ../lib

CCC	= g++
OPTFLAGS = -O9 -Wno-deprecated
CFLAGS = $(STATIC) $(OPTFLAGS)
FLAGS = $(OPTFLAGS) $(INCLUDES) 


$(APP):	$(OBJS)
	$(CCC) $(CFLAGS) -o $(APP) $(OBJS) $(LIBDIRS) $(LIBS) 

$(PSTTREELIB): $(OBJS)
	ar crv $(PSTTREELIB) $(OBJS)

clean:
	/bin/rm -f $(APP) $(PSTTREELIB) $(OBJS) *~ *.bak

install: $(PSTTREELIB)
	cp -pf $(PSTTREELIB) $(PSTTREELIBDIR)


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
