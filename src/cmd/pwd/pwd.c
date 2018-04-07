#include "pwd.h"

int pwd(){
    char tampon[100];

    if (getcwd (tampon, 100) == NULL) {
        return 0;
    }
    puts (tampon);
    return 0;
}
