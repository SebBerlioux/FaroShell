#include "exit.h"

int fexit(int argc, char const *argv[]){
  char const *fonction = argv[0];

  if(argc>1){
    printf("%s: Too many argument(s)\n", fonction);
    return 1;
  }

  exit(EXIT_SUCCESS);
}
