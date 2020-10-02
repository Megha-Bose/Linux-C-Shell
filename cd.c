#include "headers.h"

void cd(char *path) 
{
    if(path == NULL)
    {
        int temp = chdir(HOME);
        if (temp < 0)
            perror(DFLT "change directory error");
        return; 
    }

    char delim[] = " \n\t\r";
    char *s = (char *) malloc(sizeof(char) * MX_L2);                // handling extra spaces, tabs etc. in the path entered
    strcpy(s, path);
    char *token;
    token = strtok(s, delim);
    if (strcmp("~", token) == 0 || strcmp("", path) == 0)
        token = HOME;
    else if(strcmp("-", token) == 0)
    {
        char *found, *pseu;
        char *lastdir = (char *) malloc(sizeof(char) * MX_L2);
        strcpy(lastdir, LWD);
        found = strstr(lastdir, HOME);
        if(found)
        {
            pseu = found + strlen(HOME);
            char *home = (char *) malloc(256 * sizeof(char));
            strcpy(home, "~"); strcat(home,pseu); strcpy(pseu,home);
            printf("%s\n",pseu);
            free(home);
        }
        else
            printf("%s", LWD);
        token = get_abs_path(LWD);
        free(lastdir);
    }                                               
    else
        token = get_abs_path(path);                                 // else get absolute path
    int temp = chdir(token);
    if (temp < 0)
    {
        perror(DFLT "change directory error");
        strcpy(emoji,":'(");
    }
    else
    {
        char *dir = (char *) malloc(sizeof(char) * MX_L2);
        strcpy(dir, LWD);
        char *dirr = (char *) malloc(sizeof(char) * MX_L2);
        
        strcpy(dirr, CWD1);
        strcpy(LWD, dirr);
        dir = getcwd(NULL, 0);
        strcpy(CWD1, dir);

        free(dir);
        free(dirr);
    }
    
    free(s);
}