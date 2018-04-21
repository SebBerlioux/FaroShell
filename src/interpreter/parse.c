#include "parse.h"

void parseParamsList(SStack *stack, char* commandLine)
{
	char* argument;	// un parametre
	int buf = BUF;
	int nbArgs = 0;
	char **args = malloc(buf * sizeof(char*));

	// recupere le premier "token" avant un espace
	argument = strtok(commandLine, DELIMITERS);
	args[nbArgs] = argument;

	printf("args[%d] = %s\n", nbArgs, args[nbArgs]);
	// tant que pas fin de chaine
	while (argument != NULL)
	{
		nbArgs++;
		//AddElementEnd(liste, argument);	// ajout du parametre lu a la liste
		argument = strtok(NULL, " ");	// recupere le "token" suivant
		args[nbArgs] = argument;
		printf("args[%d] = %s\n", nbArgs, args[nbArgs]);
	}

	Arguments arguments;
	arguments.argc = nbArgs;
	arguments.argv = args;

	//push_elem(stack, args);

}
/*
void executeCommand(SList *liste)
{
	if (GetData(GetFirstElement(liste)))
	{
		//printf("Debug\n");
		char *cmd = GetData(GetFirstElement(liste));
		int nbArgs;

		//DeleteCell(liste, GetFirstElement(liste));
		nbArgs = GetSize(liste);
		char *args[nbArgs];

		SCell *cell = GetFirstElement(liste);
		for (int i = 0; i < nbArgs; i++)
		{
			args[i] = GetData(cell);
			cell = GetNextElement(cell);
		}
		args[nbArgs] = NULL;


		printf("nbArgs = %d\n", nbArgs);
		printf("args = %s\n", args[0]);

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
}
*/
