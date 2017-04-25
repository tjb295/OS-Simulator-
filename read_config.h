
//function prototypes
//struct configs read_config(FILE* config);
#ifndef _READ_CONFIG_H_
#define _READ_CONFIG_H_
#include "MetaData.h"

void skip_to_next(FILE* config);


typedef struct {
	int version;
	char file[FILENAME_LEN+1];
	char cpu_sched[CPU_SCHED_LEN+1];
	int cycles;
	int memory;
	int p_cycle_time;
	int io_cycle_time;
	char log_to[LOG_TO_LEN + 1];
	char log_file_path[FILEPATH_LEN+1];
	
	
} CONFIG_STR;

CONFIG_STR *read_config(FILE* config);
#endif




