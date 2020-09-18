#include "headers.h"
#include "utils.h"
#include "echo.h"

void echo(char *token) {
    char delim[] = " \n\t\r";
    token = strtok(NULL, delim);
    while (token != NULL)
    {
        printf("%s ",token);              // printing each token
        token = strtok(NULL, delim);
    }
    printf("\n");
}