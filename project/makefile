CFLAGS = -g -w -std=c99
#VPATH = cutest

all : prog

#tests : tests.c CuTest.c dequeTests.c graphTests.c graph.o deque.o
	#gcc $(CFLAGS) -o $@ $^

prog : hw5.c graph.o deque.o
	gcc $(CFLAGS) -o $@ $^ -lm

graph.o : graph.c
	gcc $(CFLAGS) -c -o $@ $< -lm 

deque.o : deque.c
	gcc $(CFLAGS) -c -o $@ $< -lm

#memcheckTests : tests
	#valgrind --tool=memcheck --leak-check=yes tests

#memcheckProg : prog
#	valgrind --tool=memcheck --leak-check=yes prog

clean :
	-rm *.o
#	-rm tests
	-rm prog
