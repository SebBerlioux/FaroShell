#Makefile
#Déclaration des variables
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
cmd = src/cmd
obj = obj
objects = lecture.o liste.o main.o parse.o
OBJS = $(patsubst %,$(obj)/%,$(objects))

.PHONY: clean ressources faroShell

all: ressources $(EXEC)

ressources:
	mkdir -p $(obj)

faroShell: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "Build successful!"

$(OBJS): $(obj)/%.o: $(interpreter)/%.c
	@echo "Compiling $@"
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf $(obj)
