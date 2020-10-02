#include "headers.h"

void echo(char *token) {
    char delim[] = " \n\t\r";
    token = strtok(NULL, delim);
    while (token != NULL)
    {
        printf(DFLT "%s ",token);              // printing each token
        token = strtok(NULL, delim);
    }
    printf("\n");
}