C = gcc
CFLAGS  = -g -Wall

default: proc_fan

proc_fan:  main.o 
	$(CC) $(CFLAGS) -o proc_fan main.o

main.o:  main.c
	$(CC) $(CFLAGS) -c main.c

clean: 
	$(RM) proc_fan *.o *~
