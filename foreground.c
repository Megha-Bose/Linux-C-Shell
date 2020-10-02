#include "headers.h"

// function for complete execution of a foreground process
void fore(char **token)
{
	pid_t pid = fork();
    
	strcpy(f_current.name, token[0]);			// storing name of current foreground process
    f_current.pid = pid;

    if (pid < 0)
    {
        perror(DFLT "fork error");
        strcpy(emoji,":'(");
    }
    else if (pid == 0)
    {
        int check = execvp(token[0], token);	// running the command in a new child process
        if (check < 0)
        {
            strcpy(emoji,":'(");
            perror(DFLT "exec error");
			return;
        }
    }
    else
    {
        int status;
        waitpid(pid, &status, WUNTRACED);		// waiting for the child process to end and then returning
        if ( WIFEXITED(status) ) 
        { 
            int exit_status = WEXITSTATUS(status);         
            if(exit_status > 0)
                strcpy(emoji,":'(");
        } 
    }
}
