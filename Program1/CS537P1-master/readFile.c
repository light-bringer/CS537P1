#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "readFile.h"

#define LINE_MAX 1000

int readFile(int pidNum) {
	
FILE *fd;
char *path;
char line[LINE_MAX];
int lineCount = 0;
int userID = geteuid();
int myID;

//construct dir path by using the pid
sprintf(path,"/proc/%d/status",pidNum);

//open the file
fd = fopen(path,"r");

if (fd == NULL) {
	puts("File cannot be opened");
	exit(-1);
}

else {
	//puts("fd is not NULL\n");
 	
	while(fgets(line,LINE_MAX,fd) != NULL)	{
		
		if (lineCount == 8 ) {	
			//puts(line);
			sscanf(line, "%*s %d", &myID);
	//		printf("%d\n", myID);
			//	strncpy(id,line+12,6);
			//	puts(id);
				//break;

		}

		lineCount = lineCount + 1;	
	}


	fclose(fd);
}

//end of function	
return myID;
}	
