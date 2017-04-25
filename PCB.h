#include "MetaData.h"
#ifndef PCB_H
#define PCB_H

typedef struct {
    int procnum;
    char state[PROC_STATE_LENGTH + 1];
} PROC_CTRL_BLOCK;
typedef struct {
    int count;
    PROC_CTRL_BLOCK *processes;
}; PROC_STR;

void executePCB(ACTION_STR *mdataPtr, CONFIG_STR *configPtr );
#endif