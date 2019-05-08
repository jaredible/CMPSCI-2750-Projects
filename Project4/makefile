CC	= gcc
CFLAGS	= -g
TARGET	= reverser
OBJS	= reverser.o stack.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

reverser.o: reverser.c stack.h
	$(CC) $(CFLAGS) -c reverser.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

.PHONY: clean
clean:
	/bin/rm -f *.o $(TARGET)
