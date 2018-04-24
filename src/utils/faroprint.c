#include "faroprint.h"

/*
    Fonction qui permet de changer la valeur "special"
*/
void setSpecial(int value)
{
    special = value;
}

/*
    Fonction qui permet de changer la valeur de "filename"
*/
void setFileName(char *fname)
{
    strcpy(filename, fname);
}

/*
    Fonction qui print de manière différente selon la valeur de "special"
*/
int faroprint(const char* format, ...)
{

    FILE *fp;
    va_list list;
    va_start(list, format);

    if (special == NO_SPECIAL)
    {
        // On fait un printf classique
        vprintf(format, list);
        va_end(list);
    }
    else if (special == REDIRECT_RIGHT)
    {
        // On ouvre le fichier et on supprime le contenu si il y en a
        fp = fopen(filename, "w");
        vfprintf(fp, format, list);
        va_end(list);
        fclose(fp);
    }
    else if (special == DOUBLE_REDIRECT_RIGHT)
    {
        // On ouvre le fichier sans supprimer le contenu pour ajouter à la fin
        fp = fopen(filename, "a");
        vfprintf(fp, format, list);
        va_end(list);
        fclose(fp);
    }
    else if (special == PIPE_AND_OR)
    {
        // On créer un fichier temporaire pour la stdin de la seconde cmd
        fp = fopen("tmp", "r+");
        vfprintf(fp, format, list);
        va_end(list);
        fclose(fp);
    }

}