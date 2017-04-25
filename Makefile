#
# For making GBM_SCHEDULE program.
#
#CC     = quantify CC
#CC     = purify CC

CC = gcc
#CC = g++



.NAMEMAX: 512


PROGRAMS = sim02

OBJECTS =  main.o metadata_read.o config_read.o PCB.o proggen.o SimpleTimer.o
          

.SUFFIXES: .cpp .o .h .c


.c.o:
	$(CC) $(OA_CFLAGS) -c -o $@ $<

.cpp.o:
	$(CC) $(CFLAGS) -c -o $@ $<

all : $(PROGRAMS) 

$(PROGRAMS) : $(OBJECTS) 
	$(CC) -o $@  $(OBJECTS) $(ALLIBS) 



clean:
	rm *o
	CCadmin -clean=all -d./

       
        

