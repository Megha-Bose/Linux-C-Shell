#include "headers.h"

// function to print the number of interrupts per CPU per IO device
void night_interrupt()
{
    FILE *fd = fopen("/proc/interrupts", "r");
    if(fd == NULL)
    {
        perror(DFLT "interrupts file error");
        strcpy(emoji,":'(");
    }
    else
    {
        char *l = r_line("/proc/interrupts", 2);
        int n = strlen(l);
        int flag = 0;
        for(int i = 0; i < n; i++)
        {
            if(l[i] == '1' && !flag)
            {
                l[i] = ' ';
                flag = 1;
            }
            if(l[i] == ':')
                l[i] = ' ';
            if(l[i] == 'I')
            {
                l[i] = '\0';
                break;
            }
        }
        printf(DFLT "%s\n",l);
        free(l);  
    }
    fclose(fd);
    return;
}

// function to print the memory waiting to be written back
void night_newborn()
{
    FILE *fd = fopen("/proc/loadavg", "r");
    if(fd == NULL)
    {
        perror(DFLT "loadavg file error");
        strcpy(emoji,":'(");
    }
    else
    {
        char *l = r_line("/proc/loadavg", 1);
        char *token = strtok(l, " ");
        char *baby;
        while(token != NULL)
        {
            baby = token;
            token = strtok(NULL, " ");
        }
        printf(DFLT "%s", baby);
        free(l);
    }
    fclose(fd);
}

// checking validity and arguments of entered nightswatch command
void nightswatch(char* token)
{
    char *delim = " \n\t\r";
    int inter;
    token = strtok(NULL, delim);
    if(token == NULL)
    {
        printf(DFLT "Invalid arguments. Please enter in the format `nightswatch -n [seconds] [newborn/interrupt].\n");
        return;
    }
    token = strtok(NULL, delim);
    if(token == NULL)
    {
        printf(DFLT "Invalid arguments. Please enter in the format `nightswatch -n [seconds] [newborn/interrupt].\n");
        return;
    }
    int n = atoi(token);
    token = strtok(NULL, delim);
    if(token == NULL)
    {
        printf(DFLT "Invalid arguments. Please enter in the format `nightswatch -n [seconds] [newborn/interrupt].\n");
        return;
    }
    if(!strcmp(token, "newborn"))
        inter = 0;
    else if(!strcmp(token, "interrupt"))
        inter = 1;
    else 
    {
        printf(DFLT "Invalid arguments. Please enter in the format `nightswatch -n [seconds] [newborn/interrupt]\n");
        return;
    } 
    if(inter)
    {
        FILE *fd = fopen("/proc/interrupts", "r");
        if(fd == NULL)
            perror(DFLT "interrupts file error");
        else
        {
            char *l = r_line("/proc/interrupts", 1);
            printf(DFLT "%s\n",l);
            free(l);  
            fclose(fd);
        }
    }
    while(true)
    {
        fd_set rfds;
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        FD_ZERO(&rfds); 
        FD_SET(0, &rfds);

        int retval; 
        retval = select(1, &rfds, NULL, NULL, &tv);
        if(retval == -1)
            perror(DFLT "select error");
        else if(retval)
        {
            retval = select(1, &rfds, NULL, NULL, &tv);
            char ch = fgetc(stdin);
            char temp = fgetc(stdin);
            if(ch == 'q')
                break;
        }

        if(inter)
            night_interrupt();
        else 
            night_newborn();
        sleep(n);   
    }
}
