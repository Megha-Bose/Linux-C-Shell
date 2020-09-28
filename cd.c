#include "headers.h"

void cd(char *path) 
{
    if(path == NULL)
    {
        int temp = chdir(HOME);
        if (temp < 0)
            perror("change directory error");
        return; 
    }
    char delim[] = " \n\t\r";
    char *s = (char *) malloc(sizeof(char) * MX_L2);                // handling extra spaces, tabs etc. in the path entered
    strcpy(s, path);
    char *token;
    token = strtok(s, delim);
    if (strcmp("~", token) == 0 || strcmp("", path) == 0)
        token = HOME;                                               // if no path given, consider home
    else
        token = get_abs_path(path);                                 // else get absolute path
    int temp = chdir(token);
    if (temp < 0)
        perror("change directory error");
    free(s);
}