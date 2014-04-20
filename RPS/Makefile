EXE = rps
OBJS = main.o rps.o

COMPILER = g++
COMPILER_OPTS = -c -g -O0 -Wall
LINKER = g++

$(EXE) : $(OBJS)
	$(LINKER) $(OBJS) -o $(EXE)

main.o : main.cpp RPS.h
	$(COMPILER) $(COMPILER_OPTS) main.cpp

rps.o : RPS.cpp
	$(COMPILER) $(COMPILER_OPTS) RPS.cpp

clean :
	-rm -f *.o $(EXE)
