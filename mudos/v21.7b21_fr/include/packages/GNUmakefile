
SRC=uids.c contrib.c sockets.c develop.c math.c 
OBJ=uids.o contrib.o sockets.o develop.o math.o 

OBJ=$(addprefix $(OBJDIR)/,$(subst .c,.o,$(SRC)))

$(OBJDIR)/%.o: %.c
	$(CC) -I$(OBJDIR) -I.. $(CFLAGS) -o $@ -c $<

all: $(OBJ)
	ar rcu packages.a $(OBJ)
	ranlib packages.a

clean:
	-rm -f *.o
	-rm -f packages.a
