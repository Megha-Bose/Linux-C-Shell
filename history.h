#ifndef HISTORY_H
#define HISTORY_H

void history_init();
void history_update(char* cmd);
void history_print(char* token);
void history_write();

#endif