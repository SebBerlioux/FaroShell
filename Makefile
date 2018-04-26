#Makefile
#Inclusion des variables
include Makefile.variables

CMDS = cat cd chgrp chmod echo ls mkdir mv pwd rm cp du
LDFLAGS = -L$(binCmd)/$(static) $(addprefix -l, $(CMDS)) -lm
LIBSOBJ = $(objCmd)/$(CMDS)/$(CMDS).o

.PHONY: clean ressources faroShell

#Déclaration des cibles pour la compilation
all: ressources utils command $(EXEC)

#Compilation des utils
utils:
	$(CC) -c -o $(obj)/faroprint.o $(src)/$(utils)/faroprint.c $(CFLAGS)

#Création du répertoire obj
ressources:
	mkdir -p $(obj)
	mkdir -p $(objCmd)

#Compilation de l'interpréteur et du shell
faroShell: $(OBJS)
	$(CC) -o $@ $^ $(obj)/$(utilsObj) $(LDFLAGS)
	@echo "Build successful!"

$(OBJS): $(obj)/%.o: $(src)/$(interpreter)/%.c
	@echo "Building $@"
	$(CC) -c -o $@ $< $(CFLAGS)

#Compilation des commandes
command: cmdRepos cmdCompil

cmdRepos:
	mkdir -p $(bin)/$(cmd)
	mkdir -p $(bin)/$(cmd)/$(static)
	mkdir -p $(bin)/$(cmd)/$(shared)

cmdCompil:
	$(foreach cmds, $(CMDS), $(MAKE) -C $(src)/$(cmd)/$(cmds);)

#Nettoyage des fichiers objet et binaires
clean:
	rm -rf $(obj)
	rm -rf $(bin)
