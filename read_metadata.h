#ifndef _READ_METADATA_H_
#define _READ_METADATA_H_
#include "MetaData.h"

//void read_mdata(FILE* mdata);




typedef struct {
	int action;
	char oper[OPER_LEN+1];
	int cycle_time;
} MDATA_STR;
typedef struct {
    int count;
    MDATA_STR *data;
} ACTION_STR;

ACTION_STR *read_mdata(FILE* mdata);
#endif

