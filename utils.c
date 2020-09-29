#include "headers.h"

// function to get path when home directory considered 
// is the directory where the shell is executed
char* get_pseudo_path() 
{
	char *found, *path;
    
    found = strstr(CWD, HOME);                                      // checks if home is part of cwd

    if(found)
    {
        path = found + strlen(HOME);
        char *home;
        home = (char *) malloc(256 * sizeof(char));
        strcpy(home, "~");
        strcat(home,path);
        strcpy(path,home);                                          // if home is in cwd, we need to print only ~ for the home part
        free(home);
    }
    else
        path = CWD;                                                 // else we print the whole path
    return path;
}

// function to get absolute path from pseudo path
char* get_abs_path(char* path)
{
    if (path[0] == '~')
    {
        ssize_t abs_len = strlen(path) + strlen(HOME);
        char* abs_path = (char*) malloc(sizeof(char) * abs_len);
        strcpy(abs_path, HOME);                                     // expanding ~
        strcat(abs_path, path + 1);                                 // taking string from after ~ and adding it to home
        return abs_path;
    }
    else
        return path;
}

// function to check if redirection present in command
int check_redirection(char *command)
{
    char *out = strstr(command, ">");
    char *in = strstr(command, "<");

    if((out != NULL) || (in != NULL))
        return 1;
    else
        return 0;
}

// function to check if pipe is present in command
int check_piping(char *command)
{
    char *pip = strstr(command, "|");
    if(pip != NULL)
        return 1;
    else
        return 0;
}