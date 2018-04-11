#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "rm.h"

int frm(int argc, char *argv[]) {
	char* fichier = NULL;
	char** commande=malloc(1024*sizeof(char)); //allocation de la place pour la liste des commandes ( volontairement beaucoup trop grande)
	int i=0;
	
	for(i=0;i<argc;i++){
		int watchdog = 0;
		int position = 0;
		                       //On parcourt la liste des arguments pour séparer les options du fichier
		if(strcmp(&argv[i][0],"-")==0){
			
			commande[position]=*argv[i];				//On ajoute kes commande dns la liste 
			position = position + 1;
		}
		
		else{
		
			if(watchdog == 0){
				
				fichier=malloc(sizeof(argv[i])); //on extrait quelle élement est le non du fichier.
				strcat(fichier,argv[i]);
				watchdog = 1;
			}
			else{
				printf("Erreur, plusiers fichiers sont présents, merci de n'utiliser cette fonction que sur un fichier à la fois.\n");
				break;
			}
			
		}
	}
	printf("Les options entrées sont ");
	int j = 0;
	for(j=0;j<(argc-1);j++){
		printf(" %s ",&commande[j]);
	}
	
	printf("\nL'élément à supprimer est %s \n",fichier);
	
	
	
	remove(fichier);
	return 0;
}