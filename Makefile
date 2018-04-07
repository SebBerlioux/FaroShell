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
libs = src/libs
obj = obj
objCmd = obj/cmd
objects = lecture.o main.o parse.o
commands = echo.o
OBJS = $(patsubst %,$(obj)/%,$(objects))
CMDS = $(patsubst %,$(objCmd)/%,$(commands))

.PHONY: clean ressources faroShell

#Déclaration des cibles pour la compilation
all: ressources command $(EXEC)

#Création du répertoire obj
ressources:
	mkdir -p $(obj)
	mkdir -p $(objCmd)

#Compilation de l'interpréteur et du shell
faroShell: $(OBJS)
	$(CC) -o $@ $^ $(LIST) $(objCmd)/echo.o $(LDFLAGS)
	@echo "Build successful!"

$(OBJS): $(obj)/%.o: $(interpreter)/%.c
	@echo "Building $@"
	$(CC) -c -o $@ $< $(CFLAGS)

#Compilation des commandes
command: $(CMDS)

$(CMDS): $(objCmd)/%.o: $(cmd)/%/echo.c
	@echo "Building $@"
	$(CC) -c -o $@ $< $(CFLAGS)

#Nettoyage des fichiers objet
clean:
	rm -rf $(obj)
