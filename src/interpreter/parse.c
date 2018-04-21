#include "parse.h"

int nb_cmds = 0;

void parseParams(char *commandLine)
{
	splitCommands(commandLine);
	for (int i = 0; i < nb_cmds; i++)
	{
		//printf("executeCommand\n");
		executeCommand(cmds[i].argc, cmds[i].argv);
	}
	nb_cmds = 0;
}

void splitCommands(char* commandLine)
{
	char* argument;	// un parametre
	int buf = BUF;
	int nbArgs = 0;
	int special = 0;
	char **args = malloc(buf * sizeof(char*));

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

void parseSpecial(int nbArgs, char *args[])
{
	for (int i = 0; i < nbArgs; i++)
	{

	}
}

void executeCommand(int nbArgs, char *args[])
{

	char *cmd;
	cmd = args[0];

	//printf("nbArgs = %d, cmd = %s\n", nbArgs, cmd);

	if (strcmp(cmd, "echo") == 0)
	{
		fecho(nbArgs, args);
	}
	else if (strcmp(cmd, "cat") == 0)
	{
		fcat(nbArgs, args);
	}
	else if (strcmp(cmd, "pwd") == 0)
	{
		fpwd();
	}
	else if (strcmp(cmd, "cd") == 0)
	{
		fcd(nbArgs, args);
	}
	else if (strcmp(cmd, "rm") == 0)
	{
		//frm(nbArgs, args);
	}
	else if (strcmp(cmd, "mv") == 0)
	{
		fmv(nbArgs, args);
	}
	else if (strcmp(cmd, "mkdir") == 0)
	{
		fmkdir(nbArgs, args);
	}
	else if (strcmp(cmd, "ls") == 0)
	{
		fls(nbArgs, args);
	}
	else if (strcmp(cmd, "chmod") == 0)
	{
		mod(nbArgs, args);
	}
	else if (strcmp(cmd, "exit") != 0)
	{
		printf("%s: command not found\n", cmd);
	}
}
