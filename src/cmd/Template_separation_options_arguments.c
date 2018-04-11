char** fichiers=malloc(1024*sizeof(char*));
char** commande=malloc(1024*sizeof(char*));  //allocation de la place pour la liste des commandes ( volontairement beaucoup trop grande)	
int i=0;
int watchdog = 0;
char* tmp = NULL;
int position1 = 0;

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
		rintf("Un fichier à été trouvé\n");
		commande[watchdog]=argv[i];   
		watchdog = watchdog+1;
		
		
		
		
//		if(watchdog == 0){                      // A utiliser uniquement si l'on veut que un seul fichier/chemin/... soit utilisé dans la commande 
//				
//			fichier=malloc(sizeof(argv[i]));   
//			strcat(fichier,argv[i]);
//			watchdog = watchdog+1;
//			printf("Le fichier à été trouvé\n");
//		}
//		else{
//			printf("Erreur, plusiers fichiers sont présents, merci de n'utiliser cette fonction que sur un fichier à la fois.\n");
//			break;
//		}
				}
}
printf("Les options entrées sont ");
int j = 0;
for(j=0;j<(argc-watchdog);j++){
	printf(" %s ",commande[j]);
}
	
printf("\nLes fichiers/chemins/... sont %s \n",fichier);
int k = 0;
for(k=0;j<(watchdog);j++){
	printf(" %s ",fichiers[k]);