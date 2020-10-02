#include "headers.h"

// function to read the nth line from a file
char* r_line(char *filename, int n)
{   
    FILE* file = fopen(filename, "r");
    char line[256];
    char *data = malloc(sizeof(char) * 256);
    int i = 0;
    while (fgets(line, sizeof(line), file)) 
    {
        i++;
        if(i == n)
            strcpy(data, line);
    }
    fclose(file);
    return data;
}

// function to get process details
void pinfo(pid_t p_id)
{
    char *exe = malloc(sizeof(char) *(50));
    char *status = malloc(sizeof(char) *(50));
    sprintf(status,"/proc/%d/status", p_id);                                                                    // getting much of stat info in an easily understandable format
    sprintf(exe,"/proc/%d/exe", p_id);                                                                          // getting symbolic link containing the pathname of the executed command

    FILE *op;
    if(!(op = fopen(status, "r")))
    {
        printf(DFLT "Process %d does not exist\n", p_id);
        strcpy(emoji,":'(");
    }
    else
    {
        fclose(op);
        char *status_data = r_line(status, 3);                                                                  
        char *memory_data = r_line(status, 18);                                                                 
        char *token1 = strtok(status_data, ":\t");                                                              // getting status info
        token1 = strtok(NULL, ":\t");
        char *token2 = strtok(memory_data, ":\t\r ");                                                           // getting memory info
        token2 = strtok(NULL, ":\t\r");
        
        char process_path[MX_L2];                                                                               
        char *path; 
        printf(DFLT "pid -- %d\nProcess Status -- %smemory (Virtual Memory) -- %sExecutable Path -- ", p_id, token1, token2); 
        int ret = readlink(exe, process_path, MX_L1);                                                           // getting executable path
        if(ret == -1)
            printf(DFLT "no path\n");
        else 
        {
            process_path[ret] = '\0'; 
            path = strstr(process_path, HOME);
            if(path)
            {
                path = path + strlen(HOME);
                printf(DFLT "~%s\n", path);
            }
            else 
                printf(DFLT "~%s\n", process_path);
        }
        free(status_data);
        free(memory_data);
    } 
    free(status);
    free(exe);
}
