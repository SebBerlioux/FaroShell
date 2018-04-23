#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <pwd.h>

#include "stack.h"
#include "liste.h"
#include "lecture.h"
#include "parse.h"

#define SHELLNAME "FaroShell"
#define EXIT_CMD "exit"

#define ANSI_COLOR_CYAN    "\x1b[96m"
#define ANSI_COLOR_YELLOW  "\x1b[93m"
#define ANSI_COLOR_RESET   "\x1b[0m"

const char *getUserName()
{
  uid_t uid = geteuid();
  struct passwd *pwd = getpwuid(uid);
  if (pwd)
  {
    return pwd->pw_name;
  }
  return "";
}

int main(void)
{
	printf("\033[H\033[2J");	// efface la console

	char tampon[100];

	char *commandLine;	// ligne de commande rentree

	do
	{
        commandLine = malloc(sizeof(char*));
		printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET":" ANSI_COLOR_CYAN "%s"
			ANSI_COLOR_RESET, getUserName(), getcwd(tampon, 100));
		printf("$ ");	// prompt
		commandLine = lireCommande();	// lecture d'une commande entiere
		if (strcmp(commandLine, ""))
		{
			// separation de chaque parametre dans une liste doublement chainee
            parseParams(commandLine);
		}
		// suppression des donnees de la commande rentree
        free(commandLine);
	}
	// fin de la boucle lorsque "exit" rentree
	while(strcmp(commandLine, EXIT_CMD));
	printf("Goodbye !\n");

	return 0;
}
