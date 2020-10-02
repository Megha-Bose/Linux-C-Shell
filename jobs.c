#include "headers.h"

void print_jobs()
{
    char *file = malloc(sizeof(char) *(50));
    for(ll i = 0; i < num_job; i++)
    {
        ll pid = bg_jobs[i].pid;
        char name[MX_L2], status, st[MX_L1];
        strcpy(name,bg_jobs[i].name);
        sprintf(file, "/proc/%lld/status",pid);
        FILE *fd;
        fd = fopen(file,"r");
        if(fd < 0)
        {
            perror(DFLT "error: No such process\n");
            strcpy(emoji,":'(");
        }
        else
        {
            fclose(fd);
            char *status = r_line(file, 3);
            char *temp = status;
            status = strtok(status, " :\n\t\r");
            status = strtok(NULL, " :\n\t\r");

            if(status[0] == 'T')
                strcpy(status, "Stopped");
            
            else strcpy(status, "Running");
        
            printf(DFLT "[%lld] %s %s [%lld]\n",i+1, status, name, pid);
            free(temp);
        }
    }
    free(file);
}
