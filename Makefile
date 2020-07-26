CC = gcc

NCURSES_FLAGS = -lncurses

CFLAGS = $(NCURSES_FLAGS)

TARGET = prog



all: prog.c
	$(CC) $(CFLAGS) -o $(TARGET) prog.c

clean:
	$(RM) $(TARGET)
