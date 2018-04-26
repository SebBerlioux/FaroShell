#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <security/pam_appl.h>
#ifdef __APPLE__ //Test pour les utilisateurs de MacOS (G.P)
#include <security/openpam.h>
#else
#include <security/pam_misc.h>
#endif
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include "su.h"


const char D_USER[] = "root";  // Si aucun utilisateur est entré on considère que l'on cherche à se connecter à root

//Pour converser entre l'utilisateur et le programme
static struct pam_conv conv = {
    //Test pour les utilisateurs de MacOS (G.P)
    #ifdef __APPLE__  
    openpam_ttyconv,
    #else
    misc_conv,
    #endif
    NULL
};
struct passwd *pwd;

int fsu(int argc, char *argv[]) {
    pam_handle_t *pam_h = NULL;
    int val;                     // Variable qui va être utiliser pour stocker les résultats des commandes PAM
    const char *user;
    char ** env_list;            // liste des variables d'environnements
    
    user = D_USER;               //On met tout de suite l'utilisateur à sa valeur par defaut

    if(argc > 2) {               //On teste si il n'y a pas trop d'arguments dans la fonction
        fprintf(stderr, "su : trop d'arguments\n");
        return 0;
    }
    if(argc == 2) {             //Si il y a deux arguments on remplace l'utilisateur
        user = argv[1];
    }
    
    val = pam_start("check_user", user, &conv, &pam_h);  //On commence à valider 
    if (val != PAM_SUCCESS){
        fprintf(stderr, "Erreur avec le lancement de PAM\n");
    }

    if (val == PAM_SUCCESS){   //on verifie que l'utilsateur existe (impossible de lancer la commande a cause de ce test qui a un probleme de permission.
        val = pam_authenticate(pam_h, 0);
    }
    
    if (val == PAM_SUCCESS){
        val = pam_acct_mgmt(pam_h, 0);
    }
    if (val != PAM_SUCCESS) {        // On verifie que tout c'est bien passé
        fprintf(stderr, "su: Echec d'autentification\n");
        return 0;
    }


    val = pam_setcred(pam_h, 0);
    if (val != PAM_SUCCESS){
        fprintf(stderr, "Erreur avec l'utilisateur\n");
    }

    val = pam_open_session(pam_h, 0);
    if (val != PAM_SUCCESS){
        fprintf(stderr, "Erreur à l'ouverture de session\n");
    }
        
    pwd = getpwnam(user);
    if( setuid(pwd->pw_uid) != 0 ){
        fprintf(stderr, "Erreur liée à l'user_id\n");
    }


    env_list = pam_getenvlist(pam_h);
    if (env_list != NULL) {
        char ** pam_env;
        for (pam_env = env_list; *pam_env != NULL; pam_env++) {
            putenv(*pam_env);
            free(*pam_env);
        }
        free(env_list);
    } 
    else {
        fprintf(stderr, "Erreur à la récupération des paramettres\n");
        return 0;
    }


    if (pam_end(pam_h,val) != PAM_SUCCESS) { //on ferme le module et on test toujour pour voir si on trouve une erreur.
        pam_h = NULL;
        fprintf(stderr, "check_user: Echec de libération de l'autentificateur\n");
        return 0;
    }

    if (val == PAM_SUCCESS) //En cas de succes total on lance un nouveau bash avec le nouvel utilisateur.
        execvp("bash", (char*[]){"bash", NULL});

    return val;
}

