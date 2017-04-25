
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include "SimpleTimer.h"
#include "read_config.h"
#include "read_metadata.h"
#include "PCB.h"



int main(int argc, char *argv[]) {

    
    

    FILE* config = fopen(argv[1], "r");
    
    //load config file
    printf("Loading Configuration File...\n");
    CONFIG_STR *configPtr = read_config(config);
    if(configPtr == NULL) {
        fprintf(stderr,"Unable to process config file - %s\n",argv[1]);
        exit(-1);
    }
    if(configPtr->file[0] == 0) {
        fprintf(stderr,"No test file specified\n");
    }
    
    //load mdata
    printf("Loading MetaData File... \n");
    printf("\n");
    FILE* mdata = fopen(configPtr->file, "r");
    perror(mdata);
    ACTION_STR *mdataPtr = read_mdata(mdata);
    executePCB(mdataPtr, configPtr );
    
    printf("End Simulation");
    
    


}
