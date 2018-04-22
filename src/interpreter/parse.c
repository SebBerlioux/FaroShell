#include "parse.h"

/*
	Nombre de commandes dans la ligne de commande
*/
int nb_cmds = 0;

/*
	Tableau contenant le nom de toutes les commandes
*/
char *commands_name[] = {
	"cat",
	"cd",
	"chgrp",
	"chmod",
	"echo",
	"ls",
	"mkdir",
	"mv",
	"pwd",
	"rm",
	"cp"
};

/*
	Tableau contenant toutes les fonctions des commandes par pointeur de fonction
*/
int (*commands_function[]) (int, char**) = {
	&fcat,
	&fcd,
	&grp,
	&mod,
	&fecho,
	&fls,
	&fmkdir,
	&fmv,
	&fpwd,
	&frm,
	&fcp
};

/*
	Nombre de commandes dans le tableau de commandes
*/
int num_commands = sizeof(commands_name) / sizeof(char*);

/*
	Fonction qui lance le parsing de la ligne de commande en entrée
	et lance l'exécution des commandes
*/
void parseParams(char *commandLine)
{
	splitCommands(commandLine);
	for (int i = 0; i < nb_cmds; i++)
	{
		executeCommand(cmds[i].argc, cmds[i].argv);
	}
	nb_cmds = 0;
}

/*
	Fonction qui sépare les arguments de la commande et les compte
*/
void splitCommands(char* commandLine)
{
	char* argument;	// un parametre
	int nbArgs = 0;
	int special = 0;
	char **args = malloc(NOMBRE_ARGUMENT * sizeof(char*));

	// recupere le premier "token" avant un espace
	argument = strtok(commandLine, DELIMITERS);
	args[nbArgs] = argument;

	printf("args[%d] = %s\n", nbArgs, args[nbArgs]);
	// tant que pas fin de chaine
	while (argument != NULL)
	{
		if (strcmp(argument, "|") == 0)
			special = 1;
		nbArgs++;
		argument = strtok(NULL, DELIMITERS);	// recupere le "token" suivant
		args[nbArgs] = argument;
		printf("args[%d] = %s\n", nbArgs, args[nbArgs]);
	}

	if (special == 1)
		parseSpecial(nbArgs, args);
	else
	{
		Arguments arguments;
		arguments.argc = nbArgs;
		arguments.argv = args;
		cmds[nb_cmds] = arguments;
		nb_cmds++;
	}
	printf("argc = %d\n", cmds[0].argc);
}

/*

*/
void parseSpecial(int nbArgs, char *args[])
{
	int i = 0;
	int argc = 0;
	char **argv = malloc(NOMBRE_ARGUMENT * sizeof(char*));

	while (strcmp(args[i], "|"))
	{
		argv[i] = args[i];
		argc++;
	}
}

/*
	Fonction qui exécute une commande
*/
int executeCommand(int nbArgs, char *args[])
{

	char *cmd;
	cmd = args[0];
	// On parcours le tableau de commandes
	for (int i = 0; i < num_commands; i++)
	{
		if (strcmp(cmd, commands_name[i]) == 0)
		{
			// On exécute la commande grâce au tableau des pointeurs de fct
			return (*commands_function[i]) (nbArgs, args);
		}
	}

	return 0;

}
