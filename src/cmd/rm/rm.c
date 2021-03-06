#include "rm.h"
#include "../../utils/faroprint.h"

struct stat sts;    // Declaration d'une struct stat

// isAFolder prend en argument un char *testedFolder et retourne 1 si l'argument est un repertoire ou 0

int isAFolder(char* testedFolder){
    if(testedFolder!=NULL && stat(testedFolder,&sts)==0 && S_ISDIR(sts.st_mode))
        return 1;
    else return 0;
}

// Pour avoir les commantaire de chaque étape, décommenter les faroprint

int frm(int argc, char *argv[]) {

	struct stat st;          	//Ces deux variables seront utiliser pour verifier lles droits et le type des cibles
	//struct passwd *userInfo;

	char* fichier = NULL;
	char** fichiers=malloc(1024*sizeof(char*));  //allocation de la place pour la liste des fichier ( volontairement beaucoup trop grande)
	char** commande=malloc(1024*sizeof(char*));  //allocation de la place pour la liste des commandes ( volontairement beaucoup trop grande)
	char* tmp = NULL;
	int watchdog = 0;
	int position = 0;
	int R = 0;									//Les variables R et F seront utiliser pour tenir compte des options données avec la fonction
	int F = 0;

	int i=0;
	for(i=0;i<argc;i++){								//On parcourt la liste des arguments pour séparer les options du fichier
		tmp = malloc(sizeof(argv[i]));
		tmp = argv[i];
//		faroprint("%c\n",tmp[0]);

		if(tmp[0]=='-'){								   //Vérification du premier caractère de la chaine, si c'est un "-" alors la
//			faroprint("Ajout d'une commande à la liste\n");   //commande sera mise dans la liste commande
			commande[position]=argv[i];
			position = position + 1;
		}

		else{												//Si ce n'est pas un "-" c'est que c'est une cible de la fonction
//			faroprint("Un fichier à été trouvé\n");
			fichiers[watchdog]=argv[i];
			watchdog = watchdog+1;
		}
	}

	int j = 0;
	unsigned int z = 0;
	for(j=0;j<(argc-watchdog);j++){
		tmp = commande[j];

		for(z=1;z<strlen(tmp);z++){

			if(tmp[z]=='r'){
				R=1;
			}

			else if(tmp[z]=='f'){
				F=1;
			}

			else{
				faroprint("Option invalide, Seul -r et -f sont disponible");
				return 1;
			}
		}
	}

	int k = 0;

	for(k=0;k<(watchdog);k++){
		faroprint("\n %s ",fichiers[k]);
		fichier=malloc(sizeof(fichiers[k]));
		strcat(fichier,fichiers[k]);
		lstat(fichier,&st);
		if(isAFolder(fichier)){
			if(R == 1){
				if((st.st_mode & S_IWUSR)==S_IWUSR){
					remove(fichier);
					faroprint("   --  Dossier supprimé\n");
				}
				else{
					faroprint("   -- Erreur : Vous n'avez pas les droits suffisant\n");
					return 1;
				}
			}
			else{
				faroprint("   -- Erreur : La cible est un dossier\n");
				return 1;
			}
		}
		else{
			if((st.st_mode & S_IWUSR)==S_IWUSR){
				remove(fichier);
				faroprint("   -- Fichier supprimé\n");
			}
			else{
				if(F==1){
					remove(fichier);
					faroprint("   -- Fichier supprimé avec écrasement des droits\n");
				}

				else{
					faroprint("   -- Erreur vous n'avez pas les droits suffisant\n");
					return 1;
				}
			}
		}
	}
	free(fichiers);
	free(commande);
	return 0;
}
