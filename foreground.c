#include "headers.h"
#include "utils.h"
#include "foreground.h"

// function for complete execution of a foreground process
void fore(char **token)
{
	pid_t pid = fork();

	strcpy(f_current.name, token[0]);			// storing name of current foreground process
    f_current.pid = pid;

    if (pid < 0)
        perror("fork error");
    else if (pid == 0)
    {
        int check = execvp(token[0], token);	// running the command in a new child process
        if (check < 0)
        {
            perror("exec error");
			exit(EXIT_FAILURE);
        }
		exit(0);
    }
    else
    {
        int status;
        waitpid(pid, &status, WUNTRACED);		// waiting for the child process to end and then returning
    }
}
