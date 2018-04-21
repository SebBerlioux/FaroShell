#include "mv.h"

int fmv(int argc, char *argv[])
{
	int ret;
	char* source = malloc(sizeof(argv[0]));
	char* dest = malloc(sizeof(argv[1]));

	if (argc == 3)	// pas d'options
	{
		strcpy(source, argv[1]);
		strcpy(dest, argv[2]);

		ret = rename(source, dest);

		if (ret != 0)
		{
			printf("FaroShell : Impossible de déplacer le fichier/dossier \"%s\".\n", source);
		}
	}
	else if (argc > 3)
	{
		printf("FaroShell : Manque de paramètre !\n");
	}
	else
	{
		printf("FaroShell : Trop de paramètre !\n");
	}

	return 0;

}
