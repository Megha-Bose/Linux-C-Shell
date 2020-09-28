#include "headers.h"

void ctrl_c(int sig)
{
    pid_t p = getpid();
    if (p != SHELL_ID)
        return;
    if (p == SHELL_ID && f_current.pid == -1)
    {
        prompt();
        fflush(stdout);
    }
    if (f_current.pid != -1)
        kill(f_current.pid, SIGINT);
    signal(SIGINT, ctrl_c);
}

void ctrl_z(int sig)
{
    pid_t p = getpid();
    if (p != SHELL_ID)
        return;
    if (f_current.pid != -1)
    {
        kill(f_current.pid, SIGTTIN);
        kill(f_current.pid, SIGTSTP);
        bg_jobs[num_job].pid = f_current.pid;
        strcpy(bg_jobs[num_job].name, f_current.name);
        num_job++;
        return;
    }
    signal(SIGTSTP, ctrl_z);
    if (p == SHELL_ID)
    {
        prompt();
        fflush(stdout);
    }
    return;
}