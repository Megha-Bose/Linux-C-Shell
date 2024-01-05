#include "headers.h"

void ctrl_c(int sig)
{
    pid_t p = getpid();
    if(p < 0)
    {
        perror("Error");
        strcpy(emoji,":'(");
    }
    else if (p != SHELL_ID)
        return;
    if (p == SHELL_ID && f_current.pid == -1)
    {
        printf("\n");
        prompt();
        fflush(stdout);
    }
    if (f_current.pid != -1)
        kill(f_current.pid, SIGINT);
    signal(SIGINT, ctrl_c);
}

void stphandler(int sig_num) 
{ 
    pid_t p = getpid();
    if (p != SHELL_ID)
        return;
    if (f_current.pid != -1)
    {
        kill(f_current.pid, SIGTTIN);
        signal(SIGTSTP, stphandler);
        bg_jobs[num_job].pid = f_current.pid;
        strcpy(bg_jobs[num_job].name, f_current.name);
        num_job++;
        strcpy(emoji,":'(");
        printf(DFLT "%s with pid %d is suspended.\n", f_current.name, f_current.pid);
        return;
    }
    signal(SIGTSTP, stphandler);
    printf("\n");
    prompt();
    fflush(stdout);
    return;
} 
