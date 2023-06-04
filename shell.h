#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convertNumber() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096
#include "_shell.h"

extern char **environ;

/* shell_executor.c */
int shell_hsh(p_info *, char **);
int findBuiltin(p_info *);
void find_shellCMD(p_info *);
void fork_shellCMD(p_info *);

/* path_search.c */
int is_shellCMD(p_info *, char *);
char *dup_shellChars(char *, int, int);
char *find_shellPath(p_info *, char *, char *);

/* error_output.c */
void shell_Eputs(char *);
int shell_Eputchar(char);
int shell_putFD(char c, int fd);
int shell_putsFD(char *str, int fd);

/* string_utils.c */
int shell_strlen(char *);
int shell_strcmp(char *, char *);
char *startsWith(const char *, const char *);
char *shell_strcat(char *, char *);

/* string_utils_1.c */
char *shell_strcpy(char *, char *);
char *shell_strdup(const char *);
void shell_puts(char *);
int shell_putchar(char);

/* string_functions.c */
char *shell_strncpy(char *, char *, int);
char *shell_strncat(char *, char *, int);
char *shell_strchr(char *, char);

/* string_split.c */
char **splits_strToWrd(char *, char *);
char **splits_str(char *, char);

/* my_functions.c */
char *shell__memset(char *, char, unsigned int);
void s_free(char **);
void *shell_realloc(void *, unsigned int, unsigned int);

/* memory_utils.c */
int p_free(void **);

/* utility.c */
int interact(p_info *);
int isDelim(char, char *);
int shell_isAlpha(int);
int shell_atoi(char *);

/* error_utils.c */
int shell_errAtoi(char *);
void shellPrint_error(p_info *, char *);
int shellPrint_decimal(int, int);
char *convertNumber(long int, int, int);
void shell_remove(char *);

/* shell_commands.c */
int shell_exit(p_info *);
int shell_cd(p_info *);
int shell_help(p_info *);

/* alias_history.c */
int shell_history(p_info *);
int shell_alias(p_info *);

/* input_functions.c */
ssize_t shellGet_input(p_info *);
int shellGet_line(p_info *, char **, size_t *);
void shell_handler(int);

/* info.c */
void shellClear_info(p_info *);
void shellSet_info(p_info *, char **);
void shellFree_info(p_info *, int);

/* shell_functions.c */
char *shellGet_eviron(p_info *, const char *);
int shellEviron(p_info *);
int shellSetEvison(p_info *);
int shellUnsetEnviron(p_info *);
int shellPopulateEnvList(p_info *);

/* env_operations.c */
char **getEnviron(p_info *);
int unsetEnv(p_info *, char *);
int setEnv(p_info *, char *, char *);

/* history_utils.c */
char *getHistoryFile(p_info *info);
int writeHistory(p_info *info);
int readHistory(p_info *info);
int buildHistoryList(p_info *info, char *buf, int linecount);
int renumberHistory(p_info *info);

/* list_functions.c */
listS *hellAddNode(listS **, const char *, int);
listS *shellAddNodeEnd(listS **, const char *, int);
size_t shellPrintListStr(const listS *);
int shellDelNodeAtIndex(listS **, unsigned int);
void shellFreeList(listS **);

/* list_operations.c */
size_t shellListLen(const listS *);
char **shellListToStrings(listS *);
size_t shell_printList(const listS *);
listS *stringStartsWithPrefix(listS *, char *, char);
ssize_t getNodeIndex(listS *, listS *);

/* command_utils.c */
int shell_isChain(p_info *, char *, size_t *);
void checkChain(p_info *, char *, size_t *, size_t, size_t);
int replaceAlias(p_info *);
int replaceVariables(p_info *);
int replaceString(char **, char *);

#endif