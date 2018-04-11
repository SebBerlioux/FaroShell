#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "rm.h"

int frm(int argc, char *argv[]) {
	char* fichier = NULL;
	char** fichiers=malloc(1024*sizeof(char*));
	char** commande=malloc(1024*sizeof(char*));  //allocation de la place pour la liste des commandes ( volontairement beaucoup trop grande)	
	int i=0;
	int watchdog = 0;
	char* tmp = NULL;
	int position = 0;

	for(i=0;i<argc;i++){								//On parcourt la liste des arguments pour séparer les options du fichier
		tmp = malloc(sizeof(argv[i]));
		tmp = argv[i];
		printf("%c\n",tmp[0]);
		                     						
		if(tmp[0]=='-'){
				
			printf("Ajout d'une commande à la liste\n");
			commande[position]=argv[i];				   //On ajoute les commande dns la liste 
			position = position + 1;
		}
			
		else{
			printf("Un fichier à été trouvé\n");
			fichiers[watchdog]=argv[i];   
			watchdog = watchdog+1;
			}
	}
	printf("Les options entrées sont ");
	int j = 0;
	for(j=0;j<(argc-watchdog);j++){
		printf(" %s ",commande[j]);
	}
		
	printf("\nLes fichiers/chemins/... sont : ");
	int k = 0;
	for(k=0;k<(watchdog);k++){
		printf(" %s ",fichiers[k]);
		fichier=malloc(sizeof(fichiers[k]));   
		strcat(fichier,fichiers[k]);
		remove(fichier);
	}
	return 0;
}