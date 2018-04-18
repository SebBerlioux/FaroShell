#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "rm.h"
#include "IS_file.h"

// Pour avoir les commantaire de chaque étape, décommenter les printf 

int frm(int argc, char *argv[]) {
	char* fichier = NULL;
	char** fichiers=malloc(1024*sizeof(char*));
	char** commande=malloc(1024*sizeof(char*));  //allocation de la place pour la liste des commandes ( volontairement beaucoup trop grande)	
	char* tmp = NULL;
	int watchdog = 0;
	int position = 0;
	int R = 0;
	int F = 0;
	
	int i=0;
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
		
	int j = 0; //variable locale de comptage;
	int z = 0;
	for(j=0;j<(argc-watchdog);j++){
		printf("Option à analiser : %s \n",commande[j]);
		tmp = commande[j];
		
		for(z=1;z<strlen(tmp);z++){
			printf("Caractère à traiter %c \n",tmp[z]);
			
			if(tmp[z]=='r'){
				R=1;
				printf("Option r détécté\n");
				}
				
			if(tmp[z]=='f'){
				F=1;
				printf("Option f détécté\n");
				}
			
//			else{
//				printf("Option invalide, Seul -r et -f sont disponible");
//				return 1;
//			}
		}		
	}

	printf("Les options entrées sont ");
	printf("r :%i, f :%i\n",R,F);
	
	printf("\nLes fichiers/chemins/... sont : ");
	int k = 0;
	for(k=0;k<(watchdog);k++){
		printf(" %s ",fichiers[k]);
		fichier=malloc(sizeof(fichiers[k]));   
		}
		
	for(k=0;k<(watchdog);k++){
		printf(" %s ",fichiers[k]); 
		fichier=malloc(sizeof(fichiers[k]));     // Problème à régler
		strcat(fichier,fichiers[k]);
		if(isFolder(fichier)){
			if(F == 1){
				remove(fichier);
				printf("Dossier supprimé");
			}
			else{
				printf("erreur : la cible est un dossier");
			}
		}
//		else{
//			if{
//				
//			}
//			
//		}
//		remove(fichier);
	}
	return 0;
}