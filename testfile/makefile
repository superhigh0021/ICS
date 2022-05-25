CC=arm-linux-gnueabihf-gcc
EXEC=hello
OBJS=hello.c
CFLAGS+=
LDFLAGS+=

all:$(EXEC)
$(EXEC):$(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

clean:
	rm -f $(EXEC) *.elf.gdb *.o