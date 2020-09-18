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

// frquenty used colour codes
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
char HOME[MX_L2], USER[MX_L1], HOST[MX_L1], CWD[MX_L2];

pid_t SHELL_ID, CHILD_ID;
// char CHILD_NAME[1024];

typedef struct job {
    char name[MX_L1];
    pid_t pid;
} job;

ll num_job, num_bg;
job bg_jobs[MX_L2];
job f_current;

int hist_itr, hist_cnt;
char hists[20][2*MX_L2];

#endif
