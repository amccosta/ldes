CC=gcc
CXX=g++
CFLAGS=-O6 -mpentium -w
CXXFLAGS=-O6 -mpentium -w
LDFLAGS=-s -lm

OBJS=maintest.o ldmaterial.o ldmath3d.o ldobject.o \
ldparser.o ldradparser.o ldsphere.o qhsarea.o
EXEC=sphtest
LIBS=-Lqhull -lqhull

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(EXEC) $(LIBS)
