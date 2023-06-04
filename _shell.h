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
} listS;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @lineCount: the error count
 * @err_num: the error code for exit()s
 * @lineCountFlag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @envChanged: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmdBuf: address of pointer to cmdBuf, on if chaining
 * @cmdBufType: CMD_type ||, &&, ;
 * @readFD: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int lineCount;
	int err_num;
	int lineCountFlag;
	char *fname;
	listS *env;
	listS *history;
	listS *alias;
	char **environ;
	int envChanged;
	int status;

	char **cmdBuf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmdBufType; /* CMD_type ||, &&, ; */
	int readFD;
	int histcount;
} p_info;

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
	int (*func)(p_info *);
} builtin_table;