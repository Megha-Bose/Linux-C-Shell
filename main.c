#include "headers.h"

void execute_com(char *commands)
{
    char *delim = " \n\t\r";
    char *s = (char*) malloc(MX_L2 * sizeof(char));
    strcpy(s, commands);
    int n_com = 0;
    check_redirect = 0;
    check_pipe =0;
    char *temp = strtok(s, delim);
    char **tokens = malloc(256 * sizeof(char*));
    tokens[0] = temp;
    while(temp != NULL)                                            // get number of arguments
    {
        n_com++;
        temp = strtok(NULL, delim);
        tokens[n_com] = temp;
    }
    check_pipe = check_piping(commands);
    check_redirect = check_redirection(commands);
    if(check_pipe)
        piping(commands);
    else if(check_redirect)
        redirection(commands);
    else
    {
        char* com = strtok(commands, delim);                         // get the command
        if (com == NULL)                                             // check which command and execute accordingly
            return;
        else if (strcmp(com, "cd") == 0)
        {
            if(n_com > 2)
            {
                printf("cd: too many arguments\n");
                strcpy(emoji,":'(");
                return;
            }
            com = strtok(NULL, delim);
            cd(com);
        }
        else if (strcmp(com, "pwd") == 0)
            pwd();
        else if (strcmp(com, "ls") == 0)
            check_ls(com);
        else if (strcmp(com, "echo") == 0)
            echo(com);
        else if (strcmp(com, "jobs") == 0)
            print_jobs();
        else if (strcmp(com, "kjob") == 0)
            kjob(com, n_com);
        else if (strcmp(com, "fg") == 0)
            fg(com);
        else if (strcmp(com, "bg") == 0)
            bg(com);
        else if (strcmp(com, "setenv") == 0)
            set_env(com, n_com);
        else if (strcmp(com, "unsetenv") == 0)
            unset_env(com, n_com);
        else if (strcmp(com, "history") == 0)
            history_print(com);
        else if (strcmp(com, "nightswatch") == 0)
            nightswatch(com);
        else if (strcmp(com, "overkill") == 0)
            overkill();
        else if (strcmp(com, "exit") == 0 || strcmp(com, "quit") == 0)
        {
            history_write();
            overkill();
            printf(YELLOW "\n\t   Thank you for using myCShell. See you soon.\n\n" YELLOW_BOLD "\t\t\t  Sayonara!\n\n" DFLT); // exit message
            exit(EXIT_SUCCESS);
        }
        else if (strcmp(com, "pinfo") == 0)
        {
            pid_t p_id;
            if(n_com > 2)
            {
                printf("pinfo error\n");
                strcpy(emoji,":'(");
                return;
            }
            if(n_com == 1)
            {
                p_id = getpid();
                pinfo(p_id);
            }
            else
            {
                com = strtok(NULL, delim);
                p_id = atoi(com);
                pinfo(p_id);
            }
        }
        else if (strcmp(tokens[n_com - 1], "&") == 0)                   // background process
        {
            tokens[n_com - 1] = NULL;
            back(tokens);
        }
        else
            fore(tokens);
    }
    free(tokens);
    free(s);                                         
}

int main() 
{
    getcwd(HOME, sizeof(HOME));                                             // get pseudo home directory where we run the shell
    strcpy(LWD, HOME);
    strcpy(CWD1, HOME);
    getlogin_r(USER, sizeof(USER));                                         // get user
    gethostname(HOST, sizeof(HOST));                                        // get host
    SHELL_ID = getpid();
    strcpy(emoji,":')");                                                    // get shell pid

    printf(YELLOW_BOLD "\n\t\t:(:    Welcome to myCShell    :):\t\t\n\n" DFLT); // welcome message
    printf(YELLOW "\t\t  It's pretty shelly out here !\n\n" DFLT);

    size_t buffer_size = 0, inp_sz = 0;
    char* inp = NULL;                                                       // taking command input
    int num; 
    ll emoji_flag = 0;

    history_init();

    while (true) 
    {
        free(inp);                                                          // free input buffer
        signal(SIGCHLD, bg_handler);
        signal(SIGTSTP, stphandler);
        signal(SIGINT, ctrl_c);
        
        inp_sz = 0;
        buffer_size = 0;
        num = 0;

        f_current.pid = -1;
        if(emoji_flag)
            printf(DFLT "%s",emoji);
        
        strcpy(emoji,":')");
        prompt();                                                         // display prompt
        inp_sz = getline(&inp, &buffer_size, stdin);                       // get semi-colon separated commands as input
        if(inp_sz == EOF)
        {
            printf(YELLOW "\n\t   Thank you for using myCShell. See you soon.\n\n" YELLOW_BOLD "\t\t\t  Sayonara!\n\n" DFLT); // exit message
            overkill();
            exit(EXIT_SUCCESS);
        }
        if(inp[0] != '\n')
            history_update(inp);
        char *token = strtok (inp, ";");
        char **commands = malloc(256 * sizeof(char*));
        char *delim = " \n\t\r";
        while (token != NULL)
        {
            commands[num] = token;
            token = strtok (NULL, ";");
            num++;
        }
        
        for(int i = 0; i < num; i++)                                        // executing the commands one by one
        {
            emoji_flag = 1;
            strcpy(emoji,":')");
            execute_com(commands[i]);
        } 
        history_write();                                                    // writing current history back to hist.txt  
    }
}
