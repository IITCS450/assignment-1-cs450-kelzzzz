#include "common.h"
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include "ez_logger.h"

/*
Author: Kelsey Cavin
@ Illinois Institute of Technology
A20593667
*/

static void usage(const char *a){
    fprintf(stderr,"Usage: %s <cmd> [args]\n",a); 
    exit(1);
}

static double d(struct timespec a, struct timespec b){
    return (b.tv_sec-a.tv_sec)+(b.tv_nsec-a.tv_nsec)/1e9;
}

int main(int c, char**v){
    if (c < 2){ 
        usage(v[0]);
    }

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    int status;
    pid_t pid = fork();

    if (pid < 0){
        return 1;
    }

    if(pid == 0){
        execvp(v[1], &v[1]);
        exit(1);
    }else{
        if (waitpid(pid, &status, 0) == -1) {
            ERR("waitpid for %d returned -1.", pid);
            return 1;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    printf("pid=%d elapsed=%.3f exit=%d\n",pid,d(start,end),WEXITSTATUS(status));

    return 0;
}
