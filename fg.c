#include "headers.h"

void fg(char *token)
{
    char delim[] = " \n\t\r";
    token = strtok(NULL, delim);
    ll num = atoi(token);

    if (num > num_job || num < 1)
	{
		printf("Invalid job number.");
		return;
	}

    num--;
    int pid = bg_jobs[num].pid, status;
    
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
                strcpy(bg_jobs[i].name, bg_jobs[i+1].name);
                bg_jobs[i].pid = bg_jobs[i+1].pid;
            }
            num_job--;    
            break;
        }
    }

    waitpid(pid, &status, WUNTRACED);
}