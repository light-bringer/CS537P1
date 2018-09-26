#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include<stdlib.h>
#include "readFile.h"


#define LINE_MAX 1000

int listprocess() {

DIR *dir,*dir1;
struct dirent *entry, *entry1;
char *dirName = malloc(sizeof(char) *1024);
char *statusDir = malloc(sizeof(char) *1024);
FILE *fd;
int statusCount =0;
int myuserID =0;
int userID = geteuid();
char line[LINE_MAX];

if ((dir = opendir("/proc")) == NULL) {
	perror("opendir() error");
}

else {
	puts("contents of /proc: ");
	
	
	while ((entry = readdir(dir)) != NULL) {
		if(isdigit(entry->d_name[0]) !=0 ) {

	 		//printf(" %s\n", entry->d_name);

			//Builds process ID dir 
			strcpy(dirName,"/proc/");
			strcat(dirName,entry->d_name);
			
			
			if (( dir1 = opendir(dirName)) == NULL) { 
				perror(" no pid dir found");
			}
			
			//Builds status dir inside each process ID
			strcpy(statusDir,dirName);
			strcat(statusDir,"/status");		

			fd = fopen(statusDir,"r");

			if (fd == NULL) {
				puts("fd is null");
				exit(-1);
			}		
			
			//enters into status file successfully	
			else {

				myuserID = readFile(atoi(entry->d_name));
				if (userID == myuserID) {
					puts(entry->d_name);
				}
				//while ( fgets(line,LINE_MAX,fd) != NULL) {

					//puts(line);
					
				//}

			//statusCount++;	
			}

	  // printf("status: %d\n", statusCount);
	         }	
	  		

	} //end of while loop
	



}
	
	closedir(dir);
//end of main
return 0;
}



