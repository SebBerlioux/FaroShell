#include "ls.h"

const int LS_FLAG_a = 1;    //-a option
const int LS_FLAG_l = 1<<1; //-l option

char *monthName[] = {"janv.", "févr.", " mars", "avril", "  mai", " juin", "juil.", " août", "sept.", " oct.", " nov.", " déc."};

/**
 * fls
 *
 * Fonction ls
 *
 * @param  {int argc}
 * @param  {char *argv[]}
*/
int fls(int argc, char const *argv[]) {

    /*if(argc<2){
        printf("Erreur manque de paramètre !\n");
        exit(EXIT_FAILURE);
    }*/

    DIR *dirp;
    struct dirent *dptr;
    char* repertoire_courant = malloc(sizeof(char)*256);
    size_t size = 256;

    if (argv[1] == NULL)        // ou (argv == NULL || argv[1] == NULL)
        getcwd(repertoire_courant, size);
    else
        repertoire_courant = argv[1];

    if ((dirp=opendir(repertoire_courant))==NULL){
        printf("Error\n");
        return(-1);
    }

    while ((dptr=readdir(dirp))){
        if (dptr->d_name[0] != '.')
            printf("%s\n",dptr->d_name);
    }
    closedir(dirp);


    return 0;
}



/**
 * printColorFile
 *
 * Affiche le nom du fichier avec la couleur (en fonction du type de fichier)
 *
 * @param  {mode_t}  mode   Le mode_t du fichier
 * @param  {char *}  mode   Le nom du fichier à affiche
*/
void printColorFile(mode_t mode, char * path) {
    if (S_ISDIR(mode)) {                    // repertoire
        printf(BLUE "%s/", path);   //printf(BLUE "%s/" END, path); pareil sur les autres lignes x5 avant    sinon autre solution    printf("%s%s/", BLUE, path);
    } else if (S_ISLNK(mode)) {             // lien
        printf(CYAN "%s", path);
    } else if (S_ISSOCK(mode)) {            // socket
        printf(PURPLE "%s", path);
    } else if (S_ISCHR(mode) || S_ISBLK(mode) || S_ISFIFO(mode)) {
        // périphérique de caractères
        printf(YELLOW "%s", path);
    } else if ((S_IXUSR & mode) == S_IXUSR) {//exécutable
        printf(RED "%s", path);
    } else {
        printf("%s", path);
    }
}



/**
 * permission
 *
 * @param   {mode_t}    mode    Le mode du fichier à inspecter
 * @param   {char *}    perms   Le tableau de 10 caractère à remplir avec les
 *                              permissions
 *                              ex: rwxr--r--
 */
void permission(mode_t mode, char* perms) {

    perms[0] = ((S_IRUSR & mode) == S_IRUSR) ? 'r' : '-';
    perms[1] = ((S_IWUSR & mode) == S_IWUSR) ? 'w' : '-';
    perms[2] = ((S_IXUSR & mode) == S_IXUSR) ? 'x' : '-';

    perms[3] = ((S_IRGRP & mode) == S_IRGRP) ? 'r' : '-';       //Il faut remettre les define pour que ca marche
    perms[4] = ((S_IWGRP & mode) == S_IWGRP) ? 'w' : '-';
    perms[5] = ((S_IXGRP & mode) == S_IXGRP) ? 'x' : '-';

    perms[6] = ((S_IROTH & mode) == S_IROTH) ? 'r' : '-';
    perms[7] = ((S_IWOTH & mode) == S_IWOTH) ? 'w' : '-';
    perms[8] = ((S_IXOTH & mode) == S_IXOTH) ? 'x' : '-';

    perms[9] = '\0';

}




/**
 * type
 *
 * @param   {mode_t}    mode    Le mode du fichier à inspecter
 *
 * @return  {char}      Le type de fichier / dossier
 */
char type(mode_t mode) {
    if((S_IFDIR & mode) == S_IFDIR) {
        return 'd';
    } else if ((mode & S_IFLNK) == S_IFLNK) {
        return 'l';
    } else if ((mode & S_IFBLK) == S_IFBLK) {
        return 'b';
    } else if ((mode & S_IFIFO) == S_IFIFO) {
        return 'p';
    } else if ((mode & S_IFCHR) == S_IFCHR) {
        return 'c';
    } else if ((mode & S_IFSOCK) == S_IFSOCK) {
        return 's';
    } else {
        return '-';
    }
}




/**
 * isLink
 *
 * @return  {boo}   True if the file is a symlink
 */
bool isLink(mode_t mode) {
    return ((mode & S_IFLNK) == S_IFLNK);
}





/**
 * fls_file
 *
 * Print les infos sur le fichier filepath
 *
 * @param  {char *} dir
 * @param  {char *} filename
 * @param  {int}    options
 */
int fls_file(char *dir, char *filename, int options) {

    struct stat statls;
    bool optL = (options & LS_FLAG_l) == LS_FLAG_l;

    char filepath[PATH_MAX];
    sprintf(filepath, "%s/%s", dir, filename);

    if (stat(filepath, &statls) == -1) {
        perror("stat error");
        exit(EXIT_FAILURE);
    }

    if (optL) {
        char perms[10];
        permission(statls.st_mode, perms);

        struct tm *tmInfo;
        tmInfo = localtime(&statls.st_mtime);

        printf("%c", type(statls.st_mode));
        printf("%s", perms);
        printf(" ");
        printf("%3u", (unsigned int) statls.st_nlink);
        printf(" ");
        printf("%s", getpwuid(statls.st_uid)->pw_name);     //A partir de l'uid, on obtient le nom de l'utilisateur
        printf(" ");
        printf("%s", getgrgid(statls.st_gid)->gr_name);
        printf(" ");
        printf("%6d", (int) statls.st_size); // taille
        printf(" ");
        printf("%s %2d %2d:%02d\t",
               monthName[tmInfo->tm_mon],
               tmInfo->tm_mday,
               tmInfo->tm_hour,
               tmInfo->tm_min
        );
    }

    printColorFile(statls.st_mode, filename);

    if (optL) {
        if (isLink(statls.st_mode)){ //si symlink, ajout de la destination
            char buf[PATH_MAX];
            size_t len;
            if ((len = readlink(filepath, buf, sizeof(buf)-1)) != -1) {
                buf[len] = '\0';
            }
            printf(" -> %s", buf);
        }
        printf("\n");
    } else {
        printf("    ");
    }

    return 0;
}