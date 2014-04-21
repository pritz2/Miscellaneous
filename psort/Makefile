OBJS =

EXENAME = sort

COMPILER = g++ -fopenmp
WARNINGS = -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
COMPILER_OPTS = -c -g -O3 -Wfatal-errors -Werror $(WARNINGS)
LINKER = g++ -fopenmp

all: $(EXENAME)

$(EXENAME) : $(OBJS) main.o
	$(LINKER) -o $(EXENAME) $(OBJS) main.o

%.o : %.cpp $(wildcard *.h) $(wildcard *.cpp)
	$(COMPILER) $(COMPILER_OPTS) $(@:.o=.cpp) -o $@

clean:
	-rm -f *.o $(EXENAME)
