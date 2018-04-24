#include "parse.h"

/*
	Nombre de commandes dans la ligne de commande
*/
int nb_cmds = 0;

char *fileForRedirection;

char *specials_list[] = {
	"|",
	">",
	"<",
	">>",
	"<<",
	"||",
	"&&"
};

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
	int specialArg = 0;
	char **args = malloc(NOMBRE_ARGUMENT * sizeof(char*));

	// recupere le premier "token" avant un espace
	argument = strtok(commandLine, DELIMITERS);
	args[nbArgs] = argument;

	//printf("args[%d] = %s\n", nbArgs, args[nbArgs]);
	// tant que pas fin de chaine
	while (argument != NULL)
	{
		if (strcmp(argument, "|") == 0)
			specialArg = 1;
		else if (strcmp(argument, ">") == 0)
			specialArg = 2;
		else if (strcmp(argument, ">>") == 0)
			specialArg = 4;
		nbArgs++;
		argument = strtok(NULL, DELIMITERS);	// recupere le "token" suivant
		args[nbArgs] = argument;
		//printf("args[%d] = %s\n", nbArgs, args[nbArgs]);
	}

	if (specialArg)
		parseSpecial(specialArg, nbArgs, args);
	else
	{
		appendCommand(nbArgs, args);
	}
	//printf("argc = %d\n", cmds[0].argc);
}

void appendCommand(int argc, char *argv[])
{
	Arguments arguments;
	arguments.argc = argc;
	arguments.argv = argv;
	cmds[nb_cmds] = arguments;
	nb_cmds++;
}

/*
	Parse la ligne de commande si une redirection ou autre est détecté
*/
void parseSpecial(int specialArg, int nbArgs, char *args[])
{
	int i = 0;
	int argc = 0;
	char **argv = malloc(NOMBRE_ARGUMENT * sizeof(char*));
	char *specialChar = malloc(sizeof(char*));
	specialChar = specials_list[specialArg-1];

	printf("special = %s\n", specialChar);

	while (strcmp(args[i], specialChar))
	{
		argv[i] = args[i];
		printf("parse special = %s\n", argv[i]);
		i++;
		argc++;
	}

	appendCommand(argc, argv);

	int argc2 = nbArgs - argc - 1;
	free(argv);
	argv = malloc(NOMBRE_ARGUMENT * sizeof(char*));

	printf("argc = %d\nargc2 = %d\n", argc2, argc);
	for (int i = argc+1; i < nbArgs; i++) {
		argv[i] = args[i];
		printf("parse special 2 = %s\n", argv[i]);
	}

	appendCommand(argc2, argv);

	printf("nb_cmds = %d\n", nb_cmds);
	for (int i = 0; i < nb_cmds; i++)
		printf("cmds[%d].argv[0] = %s\n", i, cmds[i].argv[0]);
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
