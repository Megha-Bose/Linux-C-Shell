#ifndef LS_H
#define LS_H

int is_hidden(char *file);
void l_list(char *dir, char *file);
void ls(char* dir, int a_flag, int l_flag);
void check_ls(char *command);

#endif