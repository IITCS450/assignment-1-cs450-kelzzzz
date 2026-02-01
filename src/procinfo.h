#pragma once

/*
Author: Kelsey Cavin
@ Illinois Institute of Technology
A20593667
*/

static void build_proc_path(char proc_file[100], const char *dir, const char *pid);
static void usage(const char *a);
static void print_info(char **v, char state_buffer[256], char cmd_buffer[256], double cputime_sec);
static void check_pid_exists();
static int isnum(const char*s);
static long get_proc_long(const char *pid, const char *dir, const char *pattern);
static char* get_proc_string(const char *pid, const char *dir, const char *pattern, char *output_buffer);
static char *not_file_end(FILE *file);
static void exit_if_file_not_exists(FILE *file);
