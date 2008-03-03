CC=gcc -Wall -pedantic -ansi

all: alltom test_dict
clean:
	rm -f *.o test_dict

alltom: alltom.h dict.o alltom.o code.o
	${CC} -o alltom alltom.o dict.o code.o

test_dict: alltom.h test_dict.o dict.o
	${CC} -o test_dict test_dict.o dict.o
