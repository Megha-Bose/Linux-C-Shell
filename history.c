#include "headers.h"

// function to initialise history and loading old history as applicable
void history_init()
{
    hist_itr = 0;
    char *filename = (char*)malloc(MX_L2 * sizeof(char));
    strcpy(filename, HOME);
    strcat(filename, "/hist.txt");
    FILE *fd = fopen(filename, "r");
    while (fgets(hists[hist_itr], 2*MX_L2, fd))
    {
        int n = strlen(hists[hist_itr]);
        hists[hist_itr][n - 1] = '\0';
        strcat(hists[hist_itr],"\n");
        hist_itr++;
        if (hist_itr > 19)
            break;
    }
    hist_cnt = hist_itr;
    hist_itr %= 20;
    fclose(fd);
}

// function for storing commands in the history
void history_update(char* cmd)
{
    int ind = hist_itr - 1 + 20;
    if (strcmp(hists[ind % 20], cmd) == 0)
        return;
    else
    {
        strcpy(hists[hist_itr], cmd);
        hist_itr = (hist_itr + 1) % 20;
        if (hist_cnt < 20)
            hist_cnt++;
    }
}

// printing last 10 commands from the history
void history_print(char *token)
{
    char *delim = " \n\t\r";
    token = strtok(NULL, delim);
    int num;
    if(token == NULL)
        num = 10;
    else
        num = atoi(token);
    if(num > 20)
    {
        printf(DFLT "Number of commands needs to be less than or equal to 20.\n");
        return;
    }
    for (int i = num; i > 0; i--)
    {
        int ind = hist_itr - i + 20;
        printf("%s", hists[ind % 20]);
    }
}

// function for writing back current history
void history_write()
{
    char *filename = (char*)malloc(MX_L2 * sizeof(char));
    strcpy(filename, HOME);
    strcat(filename, "/hist.txt");
    FILE *fd = fopen(filename, "w");
    for (int i = hist_cnt; i > 0; i--)
    {
        int ind = hist_itr - i + 20;
        fputs(hists[ind % 20],fd);
    }
    fclose(fd);
    return;
}
