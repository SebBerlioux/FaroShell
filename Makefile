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

src = src
interpreter = interpreter
cmd = cmd
bin = bin
obj = obj
static = static
dynamic = dynamic
objCmd = obj/cmd
objects = lecture.o main.o parse.o liste.o
commands = echo.o
OBJS = $(patsubst %,$(obj)/%,$(objects))
CMDS = echo

.PHONY: clean ressources faroShell

#Déclaration des cibles pour la compilation
all: ressources command $(EXEC)

#Création du répertoire obj
ressources:
	mkdir -p $(obj)
	mkdir -p $(objCmd)

#Compilation de l'interpréteur et du shell
faroShell: $(OBJS)
	$(CC) -o $@ $^ $(objCmd)/echo.o $(LDFLAGS)
	@echo "Build successful!"

$(OBJS): $(obj)/%.o: $(src)/$(interpreter)/%.c
	@echo "Building $@"
	$(CC) -c -o $@ $< $(CFLAGS)

#Compilation des commandes
command: cmdRepos cmdCompil

cmdRepos:
	mkdir -p $(bin)/$(cmd)
	mkdir -p $(bin)/$(cmd)/$(static)
	mkdir -p $(bin)/$(cmd)/$(dynamic)

cmdCompil:
	$(foreach cmds, $(CMDS), $(MAKE) -C $(src)/$(cmd)/$(cmds))
#	$(CC) -c -o $@ $< $(CFLAGS)

#Nettoyage des fichiers objet
clean:
	rm -rf $(obj)
