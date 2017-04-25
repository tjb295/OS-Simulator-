#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <regex.h>
#include "read_metadata.h"

#define START_S "Start"
#define END_S "End"
#define ACTION_PATTERN "[SAMIOP]\\([a-z]+\\)[0-9]+"
#define ACTION_DELIMETER "()"

ACTION_STR *read_mdata(FILE* fp) {
    //define printing variables
    int printj;
    //define variables for taking in values
    char buffer[BUFFER_LEN + 1];
    char msgbuf[BUFFER_LEN + 1];
    char tmpBuff[BUFFER_LEN + 1];

    //allocate space for an array of mdata
    static ACTION_STR mdata;
    memset(&mdata, 0, sizeof (ACTION_STR));
    MDATA_STR *ptr = NULL;

    //pointers for keeping cursor of file
    char *cPtr = NULL;
    char *sPtr = NULL;
    
    //define regular expression variables for taking in line by line
    regex_t reg;
    regmatch_t match[2];
    int retVal;
    
    //define regular expression pattern and parameters
    retVal = regcomp(&reg, ACTION_PATTERN, REG_ICASE | REG_EXTENDED);
    if (retVal) {
        printf("Unable to compile pattern %s\n", ACTION_PATTERN);
    }
    
    //loop until we reach end of file
    while (fgets(buffer, BUFFER_LEN, fp) != NULL) {
        
	//check to make sure we made it past the first line
        if (!strncmp(buffer, START_S, strlen(START_S)) || !strncmp(buffer, END_S, strlen(END_S))) {
            continue;
        }
	
        sPtr = buffer;
        retVal = 0;
        while (retVal == 0) {
            retVal = regexec(&reg, sPtr, 1, match, 0);
            if (retVal != 0) {
               break;
            }
            memset(tmpBuff, 0, BUFFER_LEN);
            strncpy(tmpBuff, &sPtr[match[0].rm_so], match[0].rm_eo);

            sPtr += (match[0].rm_so + match[0].rm_eo); // Bump the offset for the next pattern search

            cPtr = strtok(tmpBuff, ACTION_DELIMETER);
            if (cPtr == NULL) {
                continue;
                ;
            }
            // WE should have a valid structure - allocate space for it
            mdata.data = (MDATA_STR *) realloc(mdata.data, sizeof (MDATA_STR) * (mdata.count + 1));
            assert(mdata.data);
            ptr = (MDATA_STR *) memset(&mdata.data[mdata.count++], 0, sizeof (MDATA_STR));
            
            
            //check to see if obtained action in char pointer is valid
            if(!cPtr[0] == 'S' || !cPtr[0] == 'A' || !cPtr[0] == 'P' ||
                    !cPtr[0] == 'M' || !cPtr[0] == 'I' || !cPtr[0] == 'O')
            {
                printf("Incorrect Action given");
                fclose(fp);
                exit(1);
            }
            
            // Set the Action - single character
            ptr->action = cPtr[0];
            
            //set the cPtr to the next value, operator
            cPtr = strtok(NULL, ACTION_DELIMETER);
            if (cPtr == NULL) {
                continue;
            }
            
            // Copy over the operation
            strcpy(ptr->oper, cPtr);

            cPtr = strtok(NULL, ACTION_DELIMETER);
            if (cPtr == NULL) {
                continue;
            }
            // Convert the cycle time token to an int
            ptr->cycle_time = atoi(cPtr);



        }


    }

    fclose(fp);
   

    printf("Mdata operations are as follows: \n");
    for (printj = 0; printj < mdata.count; printj++) {
        printf("Instruction set %d: \n", printj);
        printf("\n");
        printf("Command: %c \n", mdata.data[printj].action);
        printf("Operator: %s\n", mdata.data[printj].oper);
        printf("Cycle time: %d \n", mdata.data[printj].cycle_time);
        printf("\n");
    }
    return &mdata;

}
