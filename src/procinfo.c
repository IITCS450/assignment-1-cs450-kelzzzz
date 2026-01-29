#include "common.h"
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <string.h>


/*--global constants--*/
char LINE[256];
size_t LINE_SIZE = sizeof(LINE);

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
	//todo break up into functions
	char proc_file[100];

	strcpy(proc_file, "/proc/");
	strcat(proc_file,pid);
	strcat(proc_file,"/status");
	
	printf("LOG - opening proc file with path: %s \n",proc_file);

	FILE* file = fopen(proc_file,"r");

	if(!file){
		perror("Unable to open file.\n");
		return -1;
	}

	long val = -1;

	while(fgets(LINE,LINE_SIZE,file)){
		if(sscanf(LINE,pattern, &val)==1){
			break;
		}
	}

	fclose(file);
	return val;
}

int main(int c,char**v){
	if(c!=2 || !isnum(v[1])){ 
		usage(v[0]);
	}
	//todo extend to all required printouts
	//todo modify function to accept string pattern (instead of long)
	long vmrss_kb = get_proc_long(v[1],"VmRSS: %ld kB");
	printf("%ld kb\n",vmrss_kb);
	return 0;
}
