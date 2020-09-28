#include "headers.h"

void fg(char *token)
{
    char delim[] = " \n\t\r";
    token = strtok(NULL, delim);
    ll num = atoi(token);
    num--;
    ll f = 0;
    for (ll i = 0; i < num_job; i++)
    {
        if (i == num)
        {
            f = 1;
            int status;
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU,SIG_IGN);
            tcsetpgrp(STDIN_FILENO,bg_jobs[num].pid);
            f_current.pid=bg_jobs[num].pid;
            strcpy(f_current.name,bg_jobs[num].name);
            kill(bg_jobs[num].pid, SIGCONT);
            char cmd[MX_L1]; 
		    int chk = 0;
            for(int i = 0; i < num_job; i++)													// if exited process found, other processes after it
            {																					// are shifted left by one and thus the process is deleted from the array
                if(i == num)
                {
				    strcpy(cmd, bg_jobs[i].name);
                    for(int j = i; j < num_job - 1; j++)
     			    {
          			    strcpy(bg_jobs[i].name, bg_jobs[i+1].name);
          			    bg_jobs[i].pid = bg_jobs[i+1].pid;
     			    }
     			    num_job--;
                    chk = 1;      
                    break;
                }
            }
            waitpid(-1, NULL, WUNTRACED);
            tcsetpgrp(STDIN_FILENO,getpgrp());
            signal(SIGTTIN,SIG_DFL);
            signal(SIGTTOU,SIG_DFL);

        }
    }
    if (!f)
        printf("process error: No such process\n");
}