
SRC=uids.c contrib.c sockets.c develop.c math.c 
OBJ=uids.o contrib.o sockets.o develop.o math.o 

.c.o:
	$(CC) $(CFLAGS) -I.. -c $*.c

all: $(OBJ)
	ar rcu packages.a $(OBJ)
	ranlib packages.a

clean:
	-rm -f *.o
	-rm -f packages.a
