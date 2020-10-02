#ifndef HEADERS_H
#define HEADERS_H

// necessary header files included
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

// frequenty used colour codes
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"

#define GREEN_BOLD "\033[1;32m"
#define RED_BOLD "\033[1;31m"
#define YELLOW_BOLD "\033[1;33m"
#define BLUE_BOLD "\033[1;34m"

#define DFLT "\033[0m"

#define MX_L1 1024
#define MX_L2 2048
#define ll long long

// defning variables
char HOME[MX_L2], USER[MX_L1], HOST[MX_L1], CWD[MX_L2], CWD1[MX_L2], LWD[MX_L2];

pid_t SHELL_ID;
// char CHILD_NAME[1024];

typedef struct job {
    char name[MX_L1];
    pid_t pid;
} job;

ll num_job, num_bg;
job bg_jobs[MX_L2];
job f_current;
char emoji[4];

int hist_itr, hist_cnt;
int check_redirect, check_pipe;
char hists[20][2*MX_L2];

void prompt();
void pwd();
char* get_pseudo_path();
char* get_abs_path(char *path);

void execute_com(char *commands);

int check_redirection(char *command);
void redirection(char *com);
void piping(char *comm);
int check_piping(char *command);

void cd(char* path);
void echo(char* token);
char* r_line(char *filename, int n);

void print_jobs();
void kjob(char *token, int cnt);
void fg(char *token);
void bg(char *token);
void overkill();

void fore(char **token);
void bg_handler(int sig);
void back(char **token);

void set_env(char *token, int cnt);
void unset_env(char *token, int cnt);

void history_init();
void history_update(char* cmd);
void history_print(char* token);
void history_write();

int is_hidden(char *file);
void l_list(char *dir, char *file);
void ls(char* dir, int a_flag, int l_flag);
void check_ls(char *command);

void night_interrupt();
void night_newborn();
void nightswatch(char *token);

void pinfo(pid_t p_id);

void ctrl_c(int sig);
void stphandler(int sig_num);

#endif
