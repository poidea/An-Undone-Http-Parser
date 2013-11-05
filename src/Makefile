sfi_server:	main.o tcp.o
		gcc -o sfi_server main.o tcp.o
		make clean

main.o:		main.c
		gcc -c main.c

tcp.o:		tcp.c tcp.h
		gcc -c tcp.c tcp.h

clean:
		rm *.o

cleanall:
		make clean
		rm sfi_server


