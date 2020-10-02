#include "headers.h"

void set_env(char *token, int cnt)
{
    char delim[] = " \n\t\r";
    token = strtok(NULL, delim);
    char *arg1 = (char*) malloc(sizeof(char) * MX_L1);
    strcpy(arg1, token);
    token = strtok(NULL, delim);
    if (cnt == 1 || cnt > 3)
    {
        printf(DFLT "error: Incorrect number of arguments\n");
        strcpy(emoji,":'(");
    }
    else
    {
        ll x;
        if(cnt == 2)
            x = setenv(arg1, "", 1);
        else
            x = setenv(arg1, token, 1);
        if (x < 0)
        {
            perror(DFLT "error:\n");
            strcpy(emoji,":'(");
        }
    }
}

void unset_env(char *token, int cnt)
{
    char delim[] = " \n\t\r";
    token = strtok(NULL, delim);
    if (cnt != 2)
    {
        printf(DFLT "error: Incorrect number of arguments\n");
        strcpy(emoji,":'(");
    }
    else
    {
        ll x = unsetenv(token);
        if (x < 0)
        {
            perror(DFLT "error:\n");
            strcpy(emoji,":'(");
        }
    }
}
