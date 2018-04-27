#include "parse.h"
#include "../utils/faroprint.h"

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
	"cp",
	"du"
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
	&fcp,
	&fdu
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
	setSpecial(0);
	splitCommands(commandLine);
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

	int redirect = 0;
	int pipe = 0;

	// recupere le premier "token" avant un espace
	argument = strtok(commandLine, DELIMITERS);

	// tant que pas fin de chaine
	while (argument != NULL)
	{
		if (strcmp(argument, "|") == 0)
		{
			specialArg = 1;
			setSpecial(specialArg);
			int exec = executeCommand(nbArgs, args);
			if (exec == 0)
			{
				pipe = 1;
			}
			else
			{
				argument = NULL;
			}
			nbArgs = 0;
			setSpecial(0);
		}
		else if (strcmp(argument, ">") == 0)
		{
			specialArg = 2;
			redirect = 1;
		}
		else if (strcmp(argument, "<") == 0)
		{
			specialArg = 3;
		}
		else if (strcmp(argument, ">>") == 0)
		{
			specialArg = 4;
			redirect = 1;
		}
		else if (strcmp(argument, "<<") == 0)
		{
			specialArg = 5;
		}
		else if (strcmp(argument, "||") == 0)
		{
			specialArg = 6;
			setSpecial(specialArg);
			int exec = executeCommand(nbArgs, args);
			if (exec == 0)
			{
				setSpecial(0);
				executeCommand(nbArgs, args);
				argument = NULL;
			}
			else
			{
				nbArgs = 0;
				specialArg = 0;
				setSpecial(specialArg);
			}
		}
		else if (strcmp(argument, "&&") == 0)
		{
			specialArg = 7;
			setSpecial(specialArg);
			int exec = executeCommand(nbArgs, args);
			if (exec == 0)
			{
				nbArgs = 0;
				specialArg = 0;
				setSpecial(specialArg);
			}
			else
			{
				setSpecial(0);
				argument = NULL;
			}
		}
		else if (pipe == 1)
		{
			args[nbArgs] = argument;
			nbArgs++;
			args[nbArgs] = "/tmp/farotmp";
			nbArgs++;
			executeCommand(nbArgs, args);
			pipe = 0;
		}
		else if (redirect == 1)
		{
			setSpecial(specialArg);
			setFileName(argument);
			executeCommand(nbArgs, args);
			redirect = 0;
		}
		else
		{
			args[nbArgs] = argument;
			nbArgs++;
		}
		if (argument != NULL) argument = strtok(NULL, DELIMITERS);	// recupere le "token" suivant
	}
	args[nbArgs] = argument;
	if (!specialArg) executeCommand(nbArgs, args);
	else specialArg = 0;
}

/*
	Fonction qui exécute une commande
*/
int executeCommand(int nbArgs, char *args[])
{
	char *cmd;
	cmd = args[0];
	int find = 0;
	// On parcours le tableau de commandes
	for (int i = 0; i < num_commands; i++)
	{
		if (strcmp(cmd, commands_name[i]) == 0)
		{
			// On passe find à 1 pour dire que la commande existe
			find = 1;
			// On exécute la commande grâce au tableau des pointeurs de fct
			return (*commands_function[i]) (nbArgs, args);
		}
	}

	// Si find est égal à 0, on affiche que la commande n'existe pas
	if (!find && strcmp(cmd, "exit") != 0)
	{
		printf("%s: command not found\n", cmd);
		return -1;
	}

	return 0;

}
