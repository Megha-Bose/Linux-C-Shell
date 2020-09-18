#include "headers.h"
#include "pwd.h"

void pwd() 
{
    char *dir = (char *) malloc(sizeof(char) * MX_L2);
    dir = getcwd(NULL, 0);                                  // get cwd
    if (dir == NULL) 
    {
        perror("current working directory error");          // pwd error handling
        return;
    }
    printf("%s\n", dir);                                    // print cwd
    free(dir);
}