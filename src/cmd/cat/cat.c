#include "cat.h"

// ex:$ cat

void fcat(int argc, char const *argv[]){

  if(argc < 2){
    printf("Erreur, manque de parametre !\n");
    exit(EXIT_FAILURE);
  }

  FILE *fp;
  int nbOption = 0;
  char *option[] = (char*)malloc(sizeof(char));

  for(size_t i=1; i<argc; i++){
    if(strcmp(argv[i], (char*)("-A")) == 0 || strcmp(argv[i], (char*)("--show-all")) == 0 || strcmp(argv[i], (char*)("-ET")) == 0){
      // display $ at end of each line
      // display TAB characters as ^I
      nbOption += 2;
      option = (char*)realloc(option, nbOption*sizeof(char*));
      option[nbOption-2] = "E";
      option[nbOption-1] = "T";
    }
    if(strcmp(argv[i], (char*)("-b")) == 0 || strcmp(argv[i], (char*)("--number-nonblank")) == 0){
      // number nonempty output lines, overrides -n
      nbOption++;
      option = (char*)realloc(option, nbOption*sizeof(char*));
      option[nbOption-1] = "b";
    }
    if(strcmp(argv[i], (char*)("-E")) == 0 || strcmp(argv[i], (char*)("--show-ends")) == 0 || strcmp(argv[i], (char*)("-e")) == 0){
      // display $ at end of each line
      nbOption++;
      option = (char*)realloc(option, nbOption*sizeof(char*));
      option[nbOption-1] = "E";
    }
    if(strcmp(argv[i], (char*)("-n")) == 0 || strcmp(argv[i], (char*)("--number")) == 0){
      // number all output lines
      nbOption++;
      option = (char*)realloc(option, nbOption*sizeof(char*));
      option[nbOption-1] = "n";
    }
    if(strcmp(argv[i], (char*)("-T")) == 0 || strcmp(argv[i], (char*)("--show-tabs")) == 0 || strcmp(argv[i], (char*)("-t")) == 0){
      // display TAB characters as ^I
      nbOption++;
      option = (char*)realloc(option, nbOption*sizeof(char*));
      option[nbOption-1] = "T";
    }
    // if(strcmp(argv[i], (char*)("--help")) == 0){} // afficher le man ??

    // else{ fp = FILE *argv[i]; }

    // ici les possibilités d'option sont: E, T, b, n
    readFile(fp, option, nbOption);
  }
}

void readFile(FILE *fp, char *option[], int nbOption){
  FILE *stream;
  size_t len = 0;
  char read[30] = "";

  stream = fopen(fp, "r");
  if (stream == NULL){ // erreur lors de l'ouverture du fichier
    exit(EXIT_FAILURE);
  }

  int n = 1; // compteur de ligne, sera affiché si option -n

  while(fgets(read, 30, stream) != NULL){ // lecture de chaque ligne du fichier
    for(size_t j=0; j<nbOption; j++){
      if(strcmp(option[j], (char*)("n")) == 0){
        line = line + (char)("%i",n);
        n++;
      }
      if(read == "\t"){
        if(strcmp(option[j], (char*)("T")) == 0){
          line = line + "^I";
        }else{
          line = line + "\t";
        }
      }
      if(read == "\n"){
        if(strcmp(option[j], (char*)("E")) == 0){
          line = line + '$';
        }else {
          line = line + "\n";
        }
      }
    }
  }

  exit(EXIT_SUCCESS);
}
