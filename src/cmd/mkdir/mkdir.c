#include "mkdir.h"

// ATTENTION
// l'option -m ne fonctionne pas
// la fonction mkdir() ne change pas le mode pour un quelconque raison

int fmkdir(int argc, char *argv[]){

  if(argc<2){ // nombre de paramètre incorrect
    printf("Erreur manque de paramètre !\n");
    printf("Usage: mkdir [-option (argument)] [diretory_name]\n");
    return 1;
  }else{
    mode_t folderMode = 0;

    extern int optind;
    extern char *optarg;

    char *folderName;
    char opt;

    char *mod;

    while((opt = getopt(argc, argv, "m:")) != -1){
      switch(opt){
        case 'm':
          mod = optarg;
          break;
        default: // mauvaise option
          printf("Invalid option: %s doesn't exist for mkdir command\n", argv[optind-1]);
          return 1;
      }
    }
    folderName = argv[optind];

    switch(mod[0]){
        case '1':
            folderMode |= S_IXUSR;
            break;
        case '2':
            folderMode |= S_IWUSR;
            break;
        case '3':
            folderMode |= S_IWUSR | S_IXUSR;
            break;
        case '4':
            folderMode |= S_IRUSR;
            break;
        case '5':
            folderMode |= S_IRUSR | S_IXUSR;
            break;
        case '6':
            folderMode |= S_IRUSR | S_IWUSR;
            break;
        case '7':
            folderMode |= S_IRUSR | S_IWUSR | S_IXUSR;
            break;
    }

    switch(mod[1]){
        case '1':
            folderMode |= S_IXGRP;
            break;
        case '2':
            folderMode |= S_IWGRP;
            break;
        case '3':
            folderMode |= S_IWGRP | S_IXGRP;
            break;
        case '4':
            folderMode |= S_IRGRP;
            break;
        case '5':
            folderMode |= S_IRGRP | S_IXGRP;
            break;
        case '6':
            folderMode |= S_IRGRP | S_IWGRP;
            break;
        case '7':
            folderMode |= S_IRGRP | S_IWGRP | S_IXGRP;
            break;
    }

    switch(mod[2]){
        case '1':
            folderMode |= S_IXOTH;
            break;
        case '2':
            folderMode |= S_IWOTH;
            break;
        case '3':
            folderMode |= S_IWOTH | S_IXOTH;
            break;
        case '4':
            folderMode |= S_IROTH;
            break;
        case '5':
            folderMode |= S_IROTH | S_IXOTH;
            break;
        case '6':
            folderMode |= S_IROTH | S_IWOTH;
            break;
        case '7':
            folderMode |= S_IROTH | S_IWOTH | S_IXOTH;
            break;
    }

      /*  La fonction semble ne pas fonctionner, peut importe la valeur
        de folderfolderMode, le dossier créé a une permission '777'
      */
    mkdir(folderName, folderMode);
  }
<<<<<<< HEAD
=======

>>>>>>> 4509a52a743d38aaf184cedd2515ab720b2f21b9
  return 0;
}
