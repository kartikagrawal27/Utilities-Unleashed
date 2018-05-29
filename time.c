#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "format.h"
#include <sys/types.h>
#include<sys/wait.h>

int main(int argc, char *argv[])
{
        if(argc == 1 || argc == 2)
        {
                print_time_usage();
                exit(1);
        }

        struct timespec start, end;

        clock_gettime(CLOCK_MONOTONIC, &start);

        pid_t fval = fork();

        if(fval==-1)
        {
                print_fork_failed();
                exit(1);
        }

        if(fval==0)
        {
               int tempval =  execvp(argv[1], argv+1);
                if(tempval==-1)
                 print_exec_failed();

        }
        else
        {
                int status;
                waitpid(fval, &status, 0);

                clock_gettime(CLOCK_MONOTONIC, &end);
                if(WEXITSTATUS(status)!=1)
                {
                        double t1 = start.tv_nsec;
                        double t2 = end.tv_nsec;

                //clock_gettime(CLOCK_MONOTONIC, &end); 
                        double timediff =(double)(end.tv_sec - start.tv_sec)+ (double)(t2-t1)/1000000000;

                        display_results(argv, timediff);
                }
        }

}