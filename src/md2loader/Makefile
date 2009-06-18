
GCC = g++
CFLAGS = 
LFLAGS = -lGL -lglut

all: md2model.o test.o
	$(GCC) $(CFLAGS) md2model.o test.o $(LFLAGS) -o test

md2model.o: md2model.cpp md2model.h
	$(GCC) -c $(CFLAGS) md2model.cpp

test.o: test.cpp md2model.h
	$(GCC) -c $(CFLAGS) test.cpp

clean:
	rm -f *.o test
