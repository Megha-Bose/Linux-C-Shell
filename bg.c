#include "headers.h"

void bg(char *token)
{
    char delim[] = " \n\t\r";
    token = strtok(NULL, delim);
    ll num = atoi(token);
    num--;
    int f = 0;
    for(ll i = 0; i < num_job; i++)
    {
        if(i == num)
        {
            f = 1;
            kill(bg_jobs[num].pid, SIGTTIN);  
            kill(bg_jobs[num].pid,SIGCONT);
        }
    }
    if(!f)
        printf("error: No such job found\n");
}
