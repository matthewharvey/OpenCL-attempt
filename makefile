SOURCE=main.c
OBJECTS=main.o
CFLAGS=-g -Wall -Werror
all: outliers.out
outliers.out: $(OBJECTS) makefile
	gcc -o outliers.out $(OBJECTS) -lm

main.o: main.c makefile
	gcc -c -o main.o main.c $(CFLAGS)


clean:
	rm *.o
