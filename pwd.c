#include "headers.h"

void pwd() 
{
    char *dir = (char *) malloc(sizeof(char) * MX_L2);
    dir = getcwd(NULL, 0);                                  // get cwd
    if (dir == NULL) 
    {
        perror(DFLT "current working directory error");
        strcpy(emoji,":'(");          // pwd error handling
        return;
    }
    printf("%s\n", dir);                                    // print cwd
    free(dir);
}