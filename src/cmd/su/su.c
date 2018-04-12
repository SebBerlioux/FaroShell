#include "su.h"
#include "../ls/ls.h"


void fsu(int argc, char const *argv[]){

    if(argc<2){
        printf("Erreur manque de paramètre !\n");
        exit(EXIT_FAILURE);
    }
}



const char DEFAULT_USER[] = "root"; //Root est l'utilisateur par défaut (si aucun argument n'est entré)

static struct pam_conv conv = { //Pour converser entre l'utilisateur et le programme

#ifdef _SU_H
        openpam_ttyconv,
#else
        misc_conv,
#endif
        NULL
};

struct passwd *pwd;



/**
 * fsu
 *
 * Fonction de SU
 *
 * @param  {int}        argc
 * @param  {char *[]}   argv
 */
int ksu(int argc, char *argv[]) {
    pam_handle_t *pamh = NULL;
    char ** pam_env_list; // liste des variable d'environnement
    int retval;

    if(argc > 2) {
        fprintf(stderr, "ksu : trop d'arguments\n");
        exit(EXIT_FAILURE);
    }

    const char *user;
    if(argc == 2) {
        user = argv[1];
    } else {
        user = DEFAULT_USER;
    }

    retval = pam_start("check_user", user, &conv, &pamh);

    if (retval != PAM_SUCCESS)
        fprintf(stderr, "Error with pam_start\n");

    if (retval == PAM_SUCCESS) // authentification
        retval = pam_authenticate(pamh, 0);

    if (retval == PAM_SUCCESS)
        retval = pam_acct_mgmt(pamh, 0);

    if (retval != PAM_SUCCESS) { // pas le bon mdp donc on quitte
        fprintf(stderr, "ksu: Authentication failure\n");
        exit(EXIT_FAILURE);
    }


    retval = pam_setcred(pamh, 0);

    if (retval != PAM_SUCCESS)
        fprintf(stderr, "Error with user credentials\n");

    // OUVERTURE DE LA SESSION

    retval = pam_open_session(pamh, 0);
    if (retval != PAM_SUCCESS)
        fprintf(stderr, "Error with openning session\n");

    pwd = getpwnam(user);
    if( setuid(pwd->pw_uid) != 0 )
        fprintf(stderr, "Error with setting user id\n");

    // VARIABLE D ENVIRONNEMENT

    pam_env_list = pam_getenvlist(pamh);
    if (pam_env_list != NULL) {
        char ** pam_env;
        for (pam_env = pam_env_list; *pam_env != NULL; pam_env++) {
            putenv(*pam_env);
            free(*pam_env);
        }
        free(pam_env_list);
    } else {
        fprintf(stderr, "Error\n");
        exit(EXIT_FAILURE);
    }

    // FERMETURE DE LA FONCTION PAM

    if (pam_end(pamh,retval) != PAM_SUCCESS) {
        pamh = NULL;
        fprintf(stderr, "check_user: failed to release authenticator\n");
        exit(EXIT_FAILURE);
    }

    // LANCEMENT DU NOUVEAU BASH AVEC LE BON USER
    if (retval == PAM_SUCCESS)
        execvp("bash", (char*[]){"bash", NULL});

    return retval;
}