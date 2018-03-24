
CC = gcc
DEBUG = no
LDFLAGS =
EXEC = faroShell

ifeq ($(DEBUG),yes)
        CFLAGS = -g -W -Wall
else
        CFLAGS =
endif

interpreter = src/interpreter


all: $(EXEC)
	@echo "Compiling FaroShell..."

faroShell: $(interpreter)/lecture.o $(interpreter)/liste.o \
			$(interpreter)/main.o $(interpreter)/parse.o
	$(CC) -o $@ $^ $(LDFLAGS)

obj/%.o: $(interpreter)%.c
	$(CC) -o $(interpreter)/$@ -c $(interpreter)/$< $(CFLAGS)


clean:
	rm -rf *.o
