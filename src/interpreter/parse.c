#include "parse.h"
#include "../utils/faroprint.h"

/*
	Liste des caractères de rediretion
*/
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
	/*
		On commence par initialiser le caractère de rediretion à 0
		On sépare la ligne de commande en éxécutant la/les commande(s)
	*/
	setSpecial(0);
	splitCommands(commandLine);
}

/*
	Fonction qui sépare les arguments de la commande et les compte
*/
void splitCommands(char* commandLine)
{
	char* argument;	// un parametre
	int nbArgs = 0;	// nombre d'argument de la commande
	int specialArg = 0;	// caractère de redirection
	char **args = malloc(NOMBRE_ARGUMENT * sizeof(char*));	// tableau d'argument d'une commande

	int redirect = 0;	// test si présence d'un caractère de redirection (chevrons)
	int pipe = 0;	// test si présence d'un PIPE

	// recupere le premier argument avant un espace
	argument = strtok(commandLine, DELIMITERS);

	// tant que pas fin de chaine
	while (argument != NULL)
	{
		// on regarde l'argument récupéré
		if (strcmp(argument, "|") == 0)
		{
			/*
				On défini le caractère de redirection à 1 (PIPE)
				On éxécute une première fois la commande pour tester si celle
					se termine correctement
				Si c'est le cas, on met à 1 la variable de test du PIPE
				Sinon, l'argument passe à NULL pour sortir e la boucle
				Enfin, qu'un PIPE soit détecté ou non, on réinitialise
					le nombre d'argument ainsi que le caractère de redirection
			*/
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
			/*
				On défini le caractère de redirection à 2 (REDIRECT_RIGHT)
				On met à 1 la variable de test des chevrons
			*/
			specialArg = 2;
			redirect = 1;
		}
		else if (strcmp(argument, "<") == 0)
		{
			// non implémenté
		}
		else if (strcmp(argument, ">>") == 0)
		{
			/*
				On défini le caractère de redirection à 4 (DOUBLE_REDIRECT_RIGHT)
				On met à 1 la variable de test des chevrons
			*/
			specialArg = 4;
			redirect = 1;
		}
		else if (strcmp(argument, "<<") == 0)
		{
			// non implémenté
		}
		else if (strcmp(argument, "||") == 0)
		{
			/*
				On défini le caractère de redirection à 6 (OR)
				On éxécute une première fois la commande pour tester si celle
					se termine correctement
				Si c'est le cas, on réinitialise le caractère de redirection, on
					éxécute la commande une deuxième fois puis on passe l'argument
					à NULL pour sortir de la boucle
				Sinon, on réinitialise le nombre d'argument ainsi que
					le caractère de redirection
			*/
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
			/*
				On défini le caractère de redirection à 7 (AND)
				On éxécute une première fois la commande pour tester si celle
					se termine correctement
				Si c'est le cas, on réinitialise le nombre d'argument ainsi que
					le caractère de redirection
				Sinon, on réinitialise le caractère de redirection puis on
					passe l'argument à NULL pour sortir de la boucle
			*/
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
			/*
				L'argument actuel étant la commande, on l'assigne à args[0]
				On incrémente nbArgs pour assigner à args[1] l'emplacement du
					fichier temporaire contenant le résultat de la commande
					exécutée avant le PIPE puis on réincrémente nbArgs
				On exécute ensuite la nouvelle commande (après le PIPE) avec ses
					nouveaux arguments
				Enfin on met la variable de test du PIPE à 0
			*/
			args[nbArgs] = argument;
			nbArgs++;
			args[nbArgs] = "/tmp/farotmp";
			nbArgs++;
			executeCommand(nbArgs, args);
			pipe = 0;
		}
		else if (redirect == 1)
		{
			/*
				En fonction du simple ou double chevron, on modifie le caractère
					de redirection.
				L'argument actuel étant la destination, on modifie le fichier de
					destination pour la commande faroprint
				On exécute la commande pour que celle-ci print dans un fichier
					au lieu de print dans la console
				Enfin on met la variable de test des chevrons à 0
			*/
			setSpecial(specialArg);
			setFileName(argument);
			executeCommand(nbArgs, args);
			redirect = 0;
		}
		else
		{
			/*
				S'il s'agit d'un argument quelconque (commande, option, ...) on
					le place dans la liste des arguments de la commande actuelle
				On incrémente le nombre d'argument de cette commande
			*/
			args[nbArgs] = argument;
			nbArgs++;
		}
		// si l'argument actuel est différent de NULL, on récupère le "token" suivant
		if (argument != NULL) argument = strtok(NULL, DELIMITERS);
	}

	/*
		Le dernier argument étant NULL, on termine la liste d'argument de la
			commande actuelle par NULL
		Si aucun caractère de redirection n'a été lu, on exécute la commande de
			façon normale
		Sinon, on réinitialise la caractère de redirection, la commande étant
			déjà exécutée
	*/
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
