#include "mv.h"

void fmv(int argc, char const *argv[])
{
	int ret;
	char* source = malloc(sizeof(argv[0]));
	char* dest = malloc(sizeof(argv[1]));

	if (argc == 2)	// pas d'options
	{
		strcpy(source, argv[0]);
		strcpy(dest, argv[1]);

		ret = rename(source, dest);

		if (ret != 0)
		{
			printf("FaroShell : Impossible de déplacer le fichier/dossier \"%s\".\n", source);
		}
	}
	else if (argc > 2)
	{
		printf("FaroShell : Manque de paramètre !\n");
	}
	else
	{
		printf("FaroShell : Trop de paramètre !\n");
	}
}