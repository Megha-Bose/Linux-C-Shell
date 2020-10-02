#include "headers.h"

void kjob(char *token, int cnt)
{
    ll num, sig;
    char delim[] = " \n\t\r";
    token = strtok(NULL, delim);
    num = atoi(token);
    num--;
    token = strtok(NULL, delim);
    sig = atoi(token);
    ll f = 0;
    if(cnt != 3)
    {
        printf(DFLT "error: Incorrect number of arguments\n");
        strcpy(emoji,":'(");
    }
    else
    {
        if (num < num_job && num >= 0)
            kill(bg_jobs[num].pid, sig);
        else
        {
            printf(DFLT "error : No such process found\n");
            strcpy(emoji,":'(");
        }
    }
}
