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


void executePCB(ACTION_STR *mdataPtr, CONFIG_STR *configPtr )
{
    printf("Begin Simulation...\n");
    CONFIG_STR *ptr = configPtr;
    ACTION_STR *aPtr = mdataPtr;
    int processLoop;
    int action;
    int cycle_time = ptr -> cycles;
    int process_time;
    char timerbuff[BUFFER_LEN + 1];
    double startTimestamp;
    double Timestamp;
    double endTimestamp;
    double timestampcheck;
    static PROC_CTRL_BLOCK proc;
    //begin looping through process
    for (processLoop = 0; processLoop < aPtr ->count; processLoop ++)
    {
        //calculate process time
       
        process_time = (double) cycle_time * aPtr -> data[processLoop].cycle_time;
        process_time = process_time/1000;
        
        //check to see if we are starting
        if(aPtr -> data[processLoop].action == 'S' && strcmp(aPtr->data[processLoop].oper, "start") == 0)
        {
            //start timer and program
            startTimestamp = accessTimer(START_TIMER, timerbuff);
            Timestamp = startTimestamp - startTimestamp;
            printf("Time:  %f, System start \n", Timestamp);
        }
        
        
        if(aPtr -> data[processLoop].action == 'A')
        {
            if(strcmp(aPtr->data[processLoop].oper, "start") == 0){
                 Timestamp =  accessTimer(START_TIMER, timerbuff) -startTimestamp ;
                 printf("Time: %f, OS, All processes initialized to new state \n", Timestamp);
                 Timestamp =  accessTimer(START_TIMER, timerbuff) -startTimestamp ;
                 printf("Time: %f, OS, Process 0, set to running state \n", Timestamp );
            }
            
            if(strcmp(aPtr->data[processLoop].oper, "end") == 0)
            {
                 Timestamp =  accessTimer(START_TIMER, timerbuff) -startTimestamp ;
                 printf("Time: %f, OS, Process 0 set in exit state \n", Timestamp);
            }
            
        }
        
        if(aPtr -> data[processLoop].action == 'M')
        {
            
            if(strcmp(aPtr->data[processLoop].oper, "allocate") == 0)
            {
                //do allocation
                Timestamp =  accessTimer(START_TIMER, timerbuff) -startTimestamp ;
                printf("Time: %f, Process0, Memory Management allocate action. \n", Timestamp );
            }
            if(strcmp(aPtr -> data[processLoop].oper, "access")== 0)
            {
                //do access
            }
        }
        
        //input
        //printf("%s \n", aPtr -> data[processLoop].oper);
        if(aPtr -> data[processLoop].action == 'I' )
        {
            //do some input command
            Timestamp =  accessTimer(START_TIMER, timerbuff) -startTimestamp ;
            printf("Time: %f, Process 0, %s input start \n", Timestamp, aPtr->data[processLoop].oper );
             timestampcheck = Timestamp;
            do{
                Timestamp =  accessTimer(START_TIMER, timerbuff) -startTimestamp ;
                
            }while(Timestamp < process_time + timestampcheck);
            Timestamp =  accessTimer(START_TIMER, timerbuff) -startTimestamp ;
            printf("Time: %f, Process 0, %s input end \n", Timestamp, aPtr->data[processLoop].oper );
        }
        
        if(aPtr->data[processLoop].action == 'O')
        {
            Timestamp =  accessTimer(START_TIMER, timerbuff) -startTimestamp ;
            printf("Time: %f, Process 0, %s output start \n", Timestamp, aPtr->data[processLoop].oper );
            timestampcheck = Timestamp;
            do{
                Timestamp =  accessTimer(START_TIMER, timerbuff) -startTimestamp ;
                
                
            }while(Timestamp < process_time + timestampcheck);
            Timestamp =  accessTimer(START_TIMER, timerbuff) -startTimestamp ;
            printf("Time: %f, Process 0, %s output end \n", Timestamp, aPtr->data[processLoop].oper );
        }
        if(aPtr->data[processLoop].action == 'P')
        {
            Timestamp =  accessTimer(START_TIMER, timerbuff) -startTimestamp ;
            printf("Time: %f, Process 0, %s  operation start \n", Timestamp, aPtr->data[processLoop].oper );
            timestampcheck = Timestamp;
            do{
                Timestamp =  accessTimer(START_TIMER, timerbuff) -startTimestamp ;
                
                
            }while(Timestamp < process_time + timestampcheck);
            Timestamp =  accessTimer(START_TIMER, timerbuff) -startTimestamp ;
            printf("Time: %f, Process 0, %s  operation  end \n", Timestamp, aPtr->data[processLoop].oper );
        }
        
        
        
        
      
        
    }
    printf("System Stop\n");
    
}