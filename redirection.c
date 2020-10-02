#include "headers.h"

void redirection(char *command)
{
    int d_stdout = dup(STDOUT_FILENO);
    int d_stdin = dup(STDIN_FILENO);
    int inpf = 0, outf = 0, status;
    char * inp = strstr(command, "<");
    char * out = strstr(command, ">>");
    char *out_file, *inp_file;
    char *outcom[2], *incom[2];
    char* com_l = (char *) malloc(sizeof(char) * MX_L1);
    
    if(inp != NULL)
        inpf = 1;
    if(out != NULL)
        outf = 2;
    else
    {
        char *out2 = strstr(command, ">");
        if(out2 != NULL)
            outf = 1;
    }
    char *p;
    outcom[0] = command;
    if(outf)
    { 
        outcom[0] = strtok(command, ">");
        strcpy(com_l,outcom[0]);
        outcom[1] = strtok(NULL, ">");
        out_file = strtok(outcom[1], " \r\t\n");
        if(out_file == NULL)
        {
            printf(DFLT "No output file entered.\n");
            strcpy(emoji,":'(");
            return;
        }
    }
    p = outcom[0];
    if(inpf)
    { 
        int flag = 0;
        incom[0] = strtok(p, "<");
        strcpy(com_l, incom[0]);
        incom[1] = strtok(NULL, "<");
        if(incom[1] == NULL)
        {
            printf(DFLT "No input file entered.\n");
            strcpy(emoji,":'(");
            return;
        }
        inp_file = strtok(incom[1], " \n\r\t");
        struct stat f;
        if(stat(inp_file, &f) == 0 && !S_ISDIR(f.st_mode))
            flag = 1;
        if(!flag)
        {
            printf(DFLT "File does not exist.\n");
            strcpy(emoji,":'(");
            return;
        }
    }

    char *token = strtok(com_l, " \n\r\t");
    char **args = (char**)malloc(sizeof(char*) * 100);
    int arg_num = 0;
    while(token != NULL)
    {
        args[arg_num] = (char *)malloc(sizeof(char) * (strlen(com_l)+5));
        strcpy(args[arg_num], token);
        arg_num++;
        token = strtok(NULL, " \n\t\r");
    }
    args[arg_num] = NULL;
    pid_t pid = fork();
    if(pid < 0)
    {
        perror(DFLT "fork error");
        strcpy(emoji,":'(");
        return;
    }
    if(pid == 0)
    {
        if(inpf)
        {
            int fd = open(inp_file, O_RDONLY);
            if(fd < 0) 
            {
                perror(DFLT "Input redirection error");
                strcpy(emoji,":'(");
                return;
            }   
            dup2(fd, 0);
            close(fd);
        }
        if(outf)
        {
            int fd;
            if(outf == 1)
                fd = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            else if(outf == 2)
                fd = open(out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if(fd < 0)
            {
                perror(DFLT "Output redirection error");
                strcpy(emoji,":'(");
                return;
            }
            dup2(fd, 1);         
            close(fd);
        }
        if (execvp(args[0], args) < 0) 
        {    
            perror(DFLT "Command not found");
            strcpy(emoji,":'(");
            exit(EXIT_FAILURE);
        }
        
        dup2(d_stdin, 0);
        close(d_stdin);
        dup2(d_stdout, 1);
        close(d_stdout);
    }        
    else 
        while (wait(&status) != pid);
    for(int i = 0; i < arg_num; i++)
        free(args[i]);
    free(args);
}