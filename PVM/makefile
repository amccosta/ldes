CC=gcc -O2 -mpentium
PVM_ROOT=/home/pvm3/pvm3
CFLAGS=-I$(PVM_ROOT)/include
LDFLAGS=-L$(PVM_ROOT)/lib/LINUX -lpvm3 -s

MEXEC=prtracev
SEXEC=rtslave

all: $(MEXEC) $(SEXEC)

$(MEXEC): main.c
	$(CC) $< $(CFLAGS) $(LDFLAGS) -o $(MEXEC)

$(SEXEC): slave.c
	$(CC) $< $(CFLAGS) $(LDFLAGS) -o $(SEXEC)
