#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "format.h"
#include <sys/types.h>
#include<sys/wait.h>

extern char** environ;
int main(int argc, char *argv[])
{
    char** ptr = environ;
        if(argc==1)
        {
                while(*ptr)
                {
                        printf("%s\n", *ptr);
                        ptr++;
                }
        }
        else if(argc==2)
        {
                print_env_usage();
                //exit(1);
        }
 return 0;
}
