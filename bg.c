#include "headers.h"

void bg(char *token)
{
    char delim[] = " \n\t\r";
    token = strtok(NULL, delim);
    ll num = atoi(token);
    num--;
    if(num >= 0 && num < num_job)
    {
        kill(bg_jobs[num].pid, SIGTTIN);  
        kill(bg_jobs[num].pid,SIGCONT);
    }
    else
    {
        printf(DFLT "error: No such job found\n");
        strcpy(emoji,":'(");
    }
}
