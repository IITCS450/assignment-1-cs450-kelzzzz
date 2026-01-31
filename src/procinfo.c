#include "common.h"
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <string.h>
#include "procinfo.h"
#include "ez_logger.h"

/*--global constants--*/
char LINE[256];
size_t LINE_SIZE = sizeof(LINE);

int main(int c, char **v)
{
    if(c!=2 || !isnum(v[1])){ 
		usage(v[0]);
	}
	//todo extend to all required printouts
	//todo modify function to accept string pattern (instead of long)
	long vmrss_kb = get_proc_long(v[1],"VmRSS: %ld kB");
	DEBUG("%ld kb\n",vmrss_kb);
	return 0;
}

/*--helper functions*/
//todo create function prototypes, move below main
static void usage(const char *a){
	fprintf(stderr,"Usage: %s <pid>\n",a); 
	exit(1);
}

static int isnum(const char*s){
	for(;*s;s++) if(!isdigit(*s)){
		return 0; 
	}
	return 1;
}

static long get_proc_long(const char *pid, const char *pattern){
	char proc_file[100];
    build_proc_path(proc_file, pid);

	INFO("Opening proc file with path: %s", proc_file);

	FILE* file = fopen(proc_file,"r");

	exit_if_file_not_exists(file);

	long pattern_matched_value = -1;

    while (not_file_end(file))
    {
        if(sscanf(LINE, pattern, &pattern_matched_value)==1){
			break;
		}
    }

    fclose(file);
	return pattern_matched_value;
}

char *not_file_end(FILE *file)
{
    return fgets(LINE, LINE_SIZE, file);
}

static void exit_if_file_not_exists(FILE *file){
	if(!file){
		ERR("Unable to open proc file.");
		exit(1);
	}
}

void build_proc_path(char proc_file[100], const char *pid)
{
    strcpy(proc_file, "/proc/");
    strcat(proc_file, pid);
    strcat(proc_file, "/status");
}
