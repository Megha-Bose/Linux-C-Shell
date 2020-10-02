#include "headers.h"

// function to check if a file is hidden or not
int is_hidden(char *file) 
{
    if(file[0] == '.') 
        return 1;
    else 
        return 0;
}

// function to long list the files in the directory
void l_list(char *dir, char *file)
{
    char *path = (char *)malloc(sizeof(char) * (strlen(dir) + strlen(file) + 5));
    strcpy(path, dir);
    strcat(path, "/");
    strcat(path, file);

    struct stat file_stat;
    if(stat(path, &file_stat) < 0)
    {
        perror(DFLT "File error");
        strcpy(emoji,":'(");
    }
    else 
    {
        char perm[20]="";

        struct group *gr;
        gr = getgrgid(file_stat.st_gid);

        struct passwd *pw;
        pw =  getpwuid(file_stat.st_uid);

        if (S_ISDIR(file_stat.st_mode) ? strcat(perm, "d") : strcat(perm, "-"));
        if ((file_stat.st_mode & S_IRUSR) ? strcat(perm, "r") : strcat(perm, "-"));
        if ((file_stat.st_mode & S_IWUSR) ? strcat(perm, "w") : strcat(perm, "-"));
        if ((file_stat.st_mode & S_IXUSR) ? strcat(perm, "x") : strcat(perm, "-"));
        if ((file_stat.st_mode & S_IRGRP) ? strcat(perm, "r") : strcat(perm, "-"));
        if ((file_stat.st_mode & S_IWGRP) ? strcat(perm, "w") : strcat(perm, "-"));
        if ((file_stat.st_mode & S_IXGRP) ? strcat(perm, "x") : strcat(perm, "-"));
        if ((file_stat.st_mode & S_IROTH) ? strcat(perm, "r") : strcat(perm, "-"));
        if ((file_stat.st_mode & S_IWOTH) ? strcat(perm, "w") : strcat(perm, "-"));
        if ((file_stat.st_mode & S_IXOTH) ? strcat(perm, "x") : strcat(perm, "-"));

        char *time = (char *)malloc(sizeof(char) * 50); 
        strftime(time, 50, "%b  %d %H:%M", localtime( &file_stat.st_mtime));

        if(perm[0] == 'd')
            printf(DFLT "%s  %ld  %s\t%s\t%ld\t%s\t" BLUE_BOLD "%s" DFLT "\n", perm, file_stat.st_nlink, pw->pw_name,gr->gr_name, file_stat.st_size, time, file);
        else if(perm[3] == 'x')
            printf(DFLT "%s  %ld  %s\t%s\t%ld\t%s\t" GREEN_BOLD "%s" DFLT "\n", perm, file_stat.st_nlink, pw->pw_name,gr->gr_name, file_stat.st_size, time, file);
        else 
            printf(DFLT "%s  %ld  %s\t%s\t%ld\t%s\t%s\n", perm, file_stat.st_nlink, pw->pw_name,gr->gr_name, file_stat.st_size, time, file);
    }
    free(path);
}

// function to list files in the directory according to the flags
void ls(char* dir, int a_flag, int l_flag) 
{
    struct dirent **files;
    int num = scandir(dir, &files, NULL, alphasort);
    if(num < 0) {
        perror(DFLT "Directory error");
        strcpy(emoji,":'(");
        return;
    }
    for(int i = 0; i < num; i++) {
        if(a_flag == 1 || (a_flag == 0 && !is_hidden(files[i]->d_name))) {
            if(l_flag) {
                l_list(dir, files[i]->d_name);
            }
            else {
                if(files[i]->d_type == DT_DIR) {
                    printf(BLUE_BOLD "%s\n" DFLT, files[i]->d_name);
                }
                else {
                    printf(GREEN_BOLD "%s\n" DFLT,files[i]->d_name);
                }
            }
        }
        free(files[i]);
    }
    free(files);
}

// checking flags in ls
void check_ls(char *token) 
{
    int l_flag = 0;
    int a_flag = 0;
    int flag = 0;

    // handling extra spaces, tabs etc. in input command
    char delim[] = " \n\t\r";
    char** direcs = (char**) malloc(20 * sizeof(char*));
    char** p_direcs = (char**) malloc(20 * sizeof(char*));
    int k = 0;
    token = strtok(NULL, delim);
    if(token == NULL) 
    {
        ls(".",0,0);
        flag = 1;
    }
    else {
        while(token != NULL) 
        {
            if(!strcmp(token,"-l")) {
                l_flag = 1;
            }
            else if(!strcmp(token,"-a")) {
                a_flag = 1;
            }
            else if(!strcmp(token,"-al") || !strcmp(token,"-la")) {   
                l_flag = 1; 
                a_flag = 1;
            }
            else
            {
                char *abs_path = get_abs_path(token);
                direcs[k] = abs_path;
                p_direcs[k] = abs_path;
                k++;
                flag = 1;
            }
            token = strtok(NULL, delim);
        } 
        for(ll i = 0; i < k; i++)
        {
            if(k > 1) printf(DFLT "%s:\n",direcs[i]); 
            ls(p_direcs[i], a_flag, l_flag);
            if(k > 1) printf("\n");
        }    
    }
    // if only flags mentioned, list files of cwd appropriately
    if(!flag)
    {
        ls(".", a_flag, l_flag);
    }
}
