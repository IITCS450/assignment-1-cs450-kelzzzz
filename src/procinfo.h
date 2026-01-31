#pragma once
static void build_proc_path(char proc_file[100], const char *pid);
static void usage(const char *a);
static int isnum(const char*s);
static long get_proc_long(const char *pid, const char *pattern);
static char* get_proc_string(const char *pid, const char *pattern, char *output_buffer, size_t buffer_size);
static char *not_file_end(FILE *file);

static void exit_if_file_not_exists(FILE *file);
