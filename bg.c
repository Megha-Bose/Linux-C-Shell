#include "headers.h"

void bg(char *token)
{
    char delim[] = " \n\t\r";
    token = strtok(NULL, delim);
    ll num = atoi(token);
    num--;
    if(num >= 0 && num < num_job)
    {
        if(strcmp(bg_jobs[num].name,"vim") || strcmp(bg_jobs[num].name,"vi"))
            return;
        kill(bg_jobs[num].pid, SIGTTIN);  
        kill(bg_jobs[num].pid,SIGCONT);
    }
    else
        printf("error: No such job found\n");
}
