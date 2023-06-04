#ifndef _SHELL_H_
#define _SHELL_H_

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

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int shell_hsh(info_t *, char **);
int findBuiltin(info_t *);
void find_shellCMD(info_t *);
void fork_shellCMD(info_t *);

/* toem_parser.c */
int is_shellCMD(info_t *, char *);
char *dup_shellChars(char *, int, int);
char *find_shellPath(info_t *, char *, char *);

/* toem_errors.c */
void shell_Eputs(char *);
int shell_Eputchar(char);
int shell_putFD(char c, int fd);
int shell_putsFD(char *str, int fd);

/* toem_string.c */
int shell_strlen(char *);
int shell_strcmp(char *, char *);
char *startsWith(const char *, const char *);
char *shell_strcat(char *, char *);

/* toem_string1.c */
char *shell_strcpy(char *, char *);
char *shell_strdup(const char *);
void shell_puts(char *);
int shell_putchar(char);

/* toem_exits.c */
char *shell_strncpy(char *, char *, int);
char *shell_strncat(char *, char *, int);
char *shell_strchr(char *, char);

/* toem_tokenizer.c */
char **splits_strToWrd(char *, char *);
char **splits_str(char *, char);

/* toem_realloc.c */
char *shell__memset(char *, char, unsigned int);
void s_free(char **);
void *shell_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int p_free(void **);

/* toem_atoi.c */
int interact(info_t *);
int isDelim(char, char *);
int shell_isAlpha(int);
int shell_atoi(char *);

/* toem_errors1.c */
int shell_errAtoi(char *);
void shellPrint_error(info_t *, char *);
int shellPrint_decimal(int, int);
char *convertNumber(long int, int, int);
void shell_remove(char *);

/* toem_builtin.c */
int shell_exit(info_t *);
int shell_cd(info_t *);
int shell_help(info_t *);

/* toem_builtin1.c */
int shell_history(info_t *);
int shell_alias(info_t *);

/*toem_getline.c */
ssize_t shellGet_input(info_t *);
int shellGet_line(info_t *, char **, size_t *);
void shell_handler(int);

/* toem_getinfo.c */
void shellClear_info(info_t *);
void shellSet_info(info_t *, char **);
void shellFree_info(info_t *, int);

/* toem_environ.c */
char *shellGet_eviron(info_t *, const char *);
int shellEviron(info_t *);
int shellSetEvison(info_t *);
int shellUnsetEnviron(info_t *);
int shellPopulateEnvList(info_t *);

/* toem_getenv.c */
char **getEnviron(info_t *);
int unsetEnv(info_t *, char *);
int setEnv(info_t *, char *, char *);

/* toem_history.c */
char *getHistoryFile(info_t *info);
int writeHistory(info_t *info);
int readHistory(info_t *info);
int buildHistoryList(info_t *info, char *buf, int linecount);
int renumberHistory(info_t *info);

/* toem_lists.c */
list_t *hellAddNode(list_t **, const char *, int);
list_t *shellAddNodeEnd(list_t **, const char *, int);
size_t shellPrintListStr(const list_t *);
int shellDelNodeAtIndex(list_t **, unsigned int);
void shellFreeList(list_t **);

/* toem_lists1.c */
size_t shellListLen(const list_t *);
char **shellListToStrings(list_t *);
size_t shell_printList(const list_t *);
list_t *stringStartsWithPrefix(list_t *, char *, char);
ssize_t getNodeIndex(list_t *, list_t *);

/* toem_vars.c */
int shell_isChain(info_t *, char *, size_t *);
void checkChain(info_t *, char *, size_t *, size_t, size_t);
int replaceAlias(info_t *);
int replaceVariables(info_t *);
int replaceString(char **, char *);

#endif
