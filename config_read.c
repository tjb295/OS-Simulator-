
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "read_config.h"

//helper function to skip lines




//method to read in config file and store to struct

CONFIG_STR *read_config(FILE* config) {

    static CONFIG_STR config1;
    char buffer[BUFFER_LEN + 1];
    char point = fgetc(config);
    char scanbuff[28];
    double doubleBuff;

    //move past first line
    while (point != '\n') {
        point = fgetc(config);
    }
    point = fgetc(config);

    //read in value
    fscanf(config, "%s %lf", scanbuff, &doubleBuff);
     config1.version = (int) doubleBuff;

    //read in test file
    fscanf(config, "%s %s %s", scanbuff, scanbuff, config1.file);


    fscanf(config, "%s %s %s %s", scanbuff, scanbuff, scanbuff, config1.cpu_sched);
    if (strcmp(config1.cpu_sched, "NONE") == 0) {
        strncpy(config1.cpu_sched, "FCFS_N", 50);
    }

    //check to see if we have valid cpu sched type
    if (!strcmp(config1.cpu_sched, "NONE") || !strcmp(config1.cpu_sched, "FCFS-N")
            || !strcmp(config1.cpu_sched, "SJF-N") || !strcmp(config1.cpu_sched, "SRTF-P")
            || !strcmp(config1.cpu_sched, "FCFS-P") || !strcmp(config1.cpu_sched, "RR-P")) {
        printf("Error: CPU_SCHED code was not a valid input.");
        fclose(config);
        exit(1);
    }


    //change none to cpu_sched type


    //store cycles
    fscanf(config, "%s %s %s %d", scanbuff, scanbuff, scanbuff, &config1.cycles);
    
    //cycles must comply within given limits
    if (config1.cycles <= 0 || config1.cycles >= 100) {
        printf("Cycles were not within bounds \n");
        fclose(config);
        exit(1);
    }

    //store memory
    fscanf(config, "%s %s %s  %d", scanbuff, scanbuff, scanbuff, &config1.memory);

    //check to see if memory is within bounds
    if (config1.memory <= 0 || config1.memory >= 1048576) {
        printf("Error: insufficient memory amount included.");
        fclose(config);
        exit(1);
    }

    //store cycle time
    fscanf(config, "%s %s %s %s %d", scanbuff, scanbuff, scanbuff, scanbuff, &config1.p_cycle_time);

    //make sure cycle time is viable
    if (config1.p_cycle_time <= 0 || config1.p_cycle_time >= 1000) {
        printf("The process cycle time was not within limits.");
        fclose(config);
        exit(1);
    }

    //store io cycle time
    fscanf(config, "%s %s %s %s %d", scanbuff, scanbuff, scanbuff, scanbuff, &config1.io_cycle_time);
    //error check the io cycle time
    if (config1.io_cycle_time <= 0 || config1.io_cycle_time >= 10000) {
        printf("The I/O cycle time was not within bounds");
        fclose(config);
        exit(1);
    }

    //store the log to path
    fscanf(config, "%s %s %s", scanbuff, scanbuff, &config1.log_to);


    fscanf(config, "%s %s %s %s", scanbuff, scanbuff, scanbuff, &config1.log_file_path);

    fclose(config);

    //print out the files
    printf("Configuration is as follows: \n");
    printf("Version: %d \n", config1.version);
    printf("File: %s \n", config1.file);
    printf("Cpu Sched Time: %s \n", config1.cpu_sched);
    printf("Cycles: %d \n", config1.cycles);
    printf("Memory: %d \n", config1.memory);
    printf("Processor Cycle Time: %d \n", config1.p_cycle_time);
    printf("IO Cycle Time: %d \n", config1.io_cycle_time);
    printf("log to: %s \n", config1.log_to);
    printf("Log file path: %s \n", config1.log_file_path);
    printf("\n");

    return &config1;


}

