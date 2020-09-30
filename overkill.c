#include "headers.h"

void overkill()
{
    for(ll i = 0; i < num_job; i++)
        kill(bg_jobs[i].pid,9);
}
