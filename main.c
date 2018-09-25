#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "optionParser.h"
#include "main.h"

#include <sys/stat.h>
#include <sys/types.h>

int main(int argc,char* argv[])
{
        //flag is a structure containing ints for each relevent command line option(and an int for the PID argument of the p option)
        flag* cmdFlags = (flag*)malloc(sizeof(flag));

        //Sets the flags based on the command line arguments
        process(argc,argv,cmdFlags);



	info* infoHolder = (info*)malloc(sizeof(info));

	char fileName[40];
	sprintf(fileName,"/proc/%d/stat",cmdFlags->pid);

	FILE *fptr;
	char line[1200];
	char* t;

	

	//Start at 1 to match with manual documentation for proc/<pid>/stat
	int num = 1;
	

	fptr = fopen(fileName, "r");

	if(fptr == NULL){
		perror("error opening file");
	}
	else{
		while(fgets(line, sizeof(line),fptr)){
			t = strtok(line," ");
			while(t != NULL){
				if(num == 3){
					infoHolder->state = t;
				}
				if(num == 14){
					infoHolder->uTime = t;
				}
				if(num == 15){
					infoHolder->sTime = t;
				}
				t = strtok(NULL, " ");
				num++;
				

			}
		}
	}

	fclose(fptr);

	sprintf(fileName,"/proc/%d/statm",cmdFlags->pid);

        fptr = fopen(fileName, "r");


	if(fptr == NULL){

		printf("COULD NOT OPEN");
	}


	char* line2;
	line2 = (char*)malloc(200*sizeof(char));

        if(fptr == NULL){
                perror("error opening file");
        }
        else{
	       	fgets(line2, sizeof(line2),fptr);
		infoHolder->vMem = strtok(line2," ");
        }

	 printf("State: %s\nUser Time: %s\nSystem Time: %s\nVirtualMemory: %s\n",infoHolder->state, infoHolder->uTime, infoHolder->sTime,infoHolder->vMem);


        if(cmdFlags->p){
                printf("The p flag was set with pid %d\n", cmdFlags->pid);
        }
        if(cmdFlags->c){
                printf("The c flag was set\n");
        }
        if(cmdFlags->v){
                printf("The v flag was set\n");
        }
        if(cmdFlags->S){
                printf("The S flag was set\n");
        }
        if(cmdFlags->U){
                printf("The U flag was set\n");
        }
        if(cmdFlags->s){
                printf("The s flag was set\n");
        }
	

        free(cmdFlags);
	free(line2);
        free(infoHolder);
        fclose(fptr);


        return 0;
}

