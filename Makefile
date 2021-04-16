CC = gcc
CFLAGS = -O2 -Wall -g 
BOOK_INCLUDE = /home/class_projects/book_includes
BOOK_LIB = /home/class_projects/book_libs

all: poly

poly: poly.c harness.c
	$(CC) $(CFLAGS) -o poly -DPROD -DLONG -I $(BOOK_INCLUDE) poly.c harness.c -L $(BOOK_LIB) -l csapp64

asm: poly.c 
	$(CC) $(CFLAGS) -m32 -masm=intel -S -o poly.s -DPROD -DLONG -I $(BOOK_INCLUDE) poly.c 


.PHONY: clean
clean:
	-/bin/rm -f poly *.o 

.PHONY: test
test: poly
	@poly
	@poly
	@poly

