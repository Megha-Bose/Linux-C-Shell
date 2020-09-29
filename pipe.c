#include "headers.h"

void piping(char *comm)
{
    char *token = strtok (comm, "|");
    char **args = (char **)malloc(256 * sizeof(char *));
    ll num = 0;
    while(token != NULL)
    {
        args[num] = token;
        token = strtok(NULL, "|");
        num++;
    }
    int type = 0, fd[2], fdesc = 0; 
    pid_t ps;
    for(int j=0; j < num; j++)
    {
        pipe(fd);
        ps = fork();
        if(ps == 0)
        {
            dup2(fdesc, 0);
            if(args[j+1] != NULL) 
                dup2(fd[1], 1);
            close(fd[0]);
            execute_com(args[j]);
            exit(2);
        }
        else
        {

            wait(NULL);
            close(fd[1]);
            fdesc = fd[0];
        }
    }
}
