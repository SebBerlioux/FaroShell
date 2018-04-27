#include "cd.h"
#include "../../utils/faroprint.h"

int fcd(int argc, char *argv[])
{

  if(argc == 1)
  {
    struct passwd *pw = getpwuid(getuid()); // on recupère l'ID de l'utilisateur courant
    const char *homedir = pw->pw_dir; // On recupere ensuite le mot de passe qui contient le dossier personnel "HOME" de l'utilisateur
    chdir(homedir);
  }
  else if (argc == 2)
  {
    struct stat st;	//On a besoin des infos du fichier pour savoir si on peut y entrer
    lstat(argv[1], &st);

    //On teste si l'on a les droit de lecture du contenu
    if((st.st_mode & S_IRUSR)==S_IRUSR)
    {
      chdir(argv[1]);
    }
    else
    {
      faroprint("Vous n'avez pas le droit d'entrer dans ce dossier\n");
    }
  }

  return 0;

}
