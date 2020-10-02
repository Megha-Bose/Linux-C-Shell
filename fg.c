#include "headers.h"

void fg(char *token)
{
    char delim[] = " \n\t\r";
    token = strtok(NULL, delim);
    ll num = atoi(token);

    if (num > num_job || num < 1)
	{
		printf(DFLT "Invalid job number.");
        strcpy(emoji,":'(");
		return;
	}
    
    num--;
    int pid = bg_jobs[num].pid, status;
    
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU,SIG_IGN);
    tcsetpgrp(STDIN_FILENO, getpgid(bg_jobs[num].pid));
    signal(SIGTSTP, stphandler);
    kill(pid, SIGCONT);
    signal(SIGTSTP, stphandler);
    
    f_current.pid = pid;
    strcpy(f_current.name,bg_jobs[num].name);
    for(int i = 0; i < num_job; i++)													// if exited process found, other processes after it
    {																					// are shifted left by one and thus the process is deleted from the array
        if(i == num)
        {
            for(int j = i; j < num_job - 1; j++)
            {
                strcpy(bg_jobs[j].name, bg_jobs[j+1].name);
                bg_jobs[j].pid = bg_jobs[j+1].pid;
            }
            num_job--;    
            break;
        }
    }
    
    waitpid(-1, &status, WUNTRACED);
    tcsetpgrp(STDIN_FILENO,getpgrp());
    signal(SIGTTIN,SIG_DFL);
    signal(SIGTTOU,SIG_DFL);

    // if(WIFSTOPPED(status))
    // {
    //     printf("%s with PID %d suspended\n", f_current.name, pid);
    //     strcpy(bg_jobs[num_job].name, f_current.name);
    //     bg_jobs[num_job].pid = pid;
    //     num_job++;
    // }
    return;
}