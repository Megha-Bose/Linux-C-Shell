#include "headers.h"

// function to handle exit of background processes
void bg_handler(int sig)										
{
	int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);												// checking for zombie child process
    if(pid > 0)
    {
        char cmd[MX_L1]; 
		int chk = 0;
        for(int i = 0; i < num_job; i++)													// if exited process found, other processes after it
        {																					// are shifted left by one and thus the process is deleted from the array
            if(bg_jobs[i].pid == pid)
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
		if(chk && WIFEXITED(status) && WEXITSTATUS(status) == 0)							// process exited normally
        	fprintf(stderr, "\n%s with PID %d exited normally\n", cmd, pid);
        else if(chk) 
			fprintf(stderr, "\n%s with PID %d failed to exit normally\n", cmd, pid);
        if(chk) 
			prompt();
        fflush(stdout);
	}
    return;
}

// function to initiate background process
void back(char **token)
{
    pid_t pid = fork();
	
    if (pid < 0)
        perror("fork error");
    else if (pid == 0)
    {
		setpgid(0, 0);
        int check = execvp(token[0], token);												// running the command in a new child process
        if (check < 0)
		{
            perror("exec error");
		}
		exit(0);
    }
    else
    {
		int status;
        bg_jobs[num_job].pid = pid;															// storing name of last background process
        strcpy(bg_jobs[num_job].name, token[0]);											// storing job no. of last background process
		num_job++;
		printf("[%lld] %d %s\n", num_job, pid, token[0]);
    }
	return;
}
