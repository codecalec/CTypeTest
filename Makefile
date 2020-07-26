CC=gcc
CFLAGS=-D_DEFAULT_SOURCE -D_XOPEN_SOURCE=600 -std=c99 -I -Wl,-O1,--sort-common,--as-needed,-z,relro,-z,now -lncursesw

TARGET=prog

all: prog.c
	$(CC) $(CFLAGS) prog.c -o ${TARGET}

clean:
	$(RM) $(TARGET)

