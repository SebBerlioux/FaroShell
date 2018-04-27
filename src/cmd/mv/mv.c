#include "mv.h"
#include "../../utils/faroprint.h"

int fmv(int argc, char *argv[])
{
	int ret;
	char* item;
	char* dest;

	int verbose = 0;
	int info = 0;

	int c;
	char options[] = "iv";

	int rep;
	int ren = 0;

	if (argc < 3)  //Test des arguments
	{
		faroprint("FaroShell : Manque de paramètre !\n");
	}
	else
	{
		while ((c = getopt(argc, argv, options)) != -1) //On extrait les options
		switch(c)
		{
			case 'i':
				info = 1;
				break;
			case 'v':
				verbose = 1;
				break;
		}

		struct stat destStat;
		int destExist = 1;

		if (stat(argv[argc-1], &destStat) == -1)
		{
        if (errno == ENOENT)
        {
            destExist = 0;
        }
        else
        {
            perror("Stat error");
            exit(EXIT_FAILURE);
        }
    }

		for (; optind < argc-1; optind++)
		{
			item = malloc(sizeof(argv[optind]));
			strcpy(item, argv[optind]);

	    if (destExist && S_ISDIR(destStat.st_mode))
	    {
				dest = malloc(sizeof(argv[argc-1]) + strlen(basename(item)) + 2);
				strcpy(dest, argv[argc-1]);
				strcat(dest, "/");
				strcat(dest, basename(item));
			}
	 		else
		  {
		    dest = malloc(sizeof(argv[argc-1]));
				strcpy(dest, argv[argc-1]);
	    }

			if (verbose) faroprint("Destination set to : %s\n", dest);

			if (verbose) faroprint("Item to move :  \"%s\"\n", item);

			if (info)
			{
				faroprint("Voulez-vous déplacer \"%s\" vers \"%s\" ? (y/n) ", item, dest);  //On demande une confirmation
				do
				{
					rep = getc(stdin);
					if (rep == 'y')
					{
						ren = 1;
					}
					else if (rep == 'n')
					{
						ren = 0;
						faroprint("Aucunes modifications n'a été aportées.\n");
					}
					else
					{
						faroprint("Veuillez répondre par y ou n.\n");
					}
				}
				while(rep != 'y' && rep != 'n');
			}
			else
			{
				ren = 1;
			}

			if (ren)
			{
				ret = rename(item, dest); //on déplace l'objet.
				if (ret != 0)
				{
					faroprint("FaroShell : Impossible de déplacer l'élément suivant : \"%s\".\n", item);
				}
				else
				{
					if (verbose) faroprint("L'élément \"%s\" a été déplacé vers : \"%s\"\n", item, dest);
				}
			}
			free(item);
			free(dest);
		}
	}

	return 0;

}
