#include "headers.h"

// a shell prompt of the form <username@system_name:curr_dir>
void prompt() 
{
    char *pseudo_path, *abs_path;
    abs_path = getcwd(CWD, sizeof(CWD));                                                                // gets the current working directory
    if (abs_path == NULL) {
       perror(DFLT "current directory error");
       strcpy(emoji,":'(");
       exit(EXIT_FAILURE);
    }
    else
    {
        pseudo_path = get_pseudo_path();                                                                // getting path taking cwd as the new home
        printf(DFLT "<" GREEN_BOLD "%s@%s" DFLT ":" BLUE "%s" DFLT "> ", USER, HOST, pseudo_path);      // print prompt
    }
}
