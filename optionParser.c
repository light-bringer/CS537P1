#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "optionParser.h"


//argc and argv of command line
//
int process(int argc,char* argv[], flag* cmdFlags)
{
        int opt;

        cmdFlags->p = 0;
        cmdFlags->pid = 0;
        cmdFlags->s = 0;
        cmdFlags->U = 0;
        cmdFlags->S = 0;
        cmdFlags->v = 0;
        cmdFlags->c = 0;


        while ((opt = getopt(argc, argv, "cvSUsp:")) != -1) {
                switch (opt) {
                case 'c':
                   cmdFlags->c = 1;
                   break;
                case 'v':
                   cmdFlags->v = 1;
                   break;
                case 'S':
                   cmdFlags->S = 1;
                   break;
                case 'U':
                   cmdFlags->U = 1;
                   break;
                case 's':
                   cmdFlags->s = 1;
                   break;
                case 'p':
                   cmdFlags->p = 1;
		   
                   cmdFlags->pid = atoi(optarg);
                   break;
                default:
                   break;
               }
           }


        return 0;
}
