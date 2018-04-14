#Makefile
#Inclusion des variables
include Makefile.variables

CMDS = mkdir cd cat mv rm echo pwd ls
LDFLAGS = -L$(binCmd)/$(static) $(addprefix -l, $(CMDS)) -lm
LIBSOBJ = $(objCmd)/$(CMDS)/$(CMDS).o

.PHONY: clean ressources faroShell

#Déclaration des cibles pour la compilation
all: ressources command $(EXEC)

#Création du répertoire obj
ressources:
	mkdir -p $(obj)
	mkdir -p $(objCmd)

#Compilation de l'interpréteur et du shell
faroShell: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
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
