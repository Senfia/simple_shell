#ifndef _HEADERS_H_
#define _HEADERS_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>

#define BUFFSIZE 1024
#define TOKN_BUFFSIZ 128
#define PATH_MAX  4096
#define TOKN_DELIM " \t\r\n\a"

extern char **environ;

/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;

/* list1.c */
sep_list *addSepTo_node(sep_list **head, char sep);
void freeSepTo_node(sep_list **head);
line_list *addLinTo_node(line_list **head, char *line);
void freeLinTo_node(line_list **head);

/* lists2.c */
void freeVarLi(r_var **head);
r_var *addVarTonode(r_var **head, int lvar, char *var, int lval);

/* string functions */
char *_StirCpy(char *dest, char *src);
char *_StriCat(char *dest, const char *src);
int _StirSpn(char *s, char *accept);
int _StirCmpr(char *s1, char *s2);
char *_StriChr(char *s, char c);

/* mem.c */
void *_reallcmem(void *ptr, unsigned int old_size, unsigned int new_size);
void _memCopy(void *newptr, const void *ptr, unsigned int size);
char **_reallocmemdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* _str2.c */
char *_striDup(const char *s);
int _striLength(const char *s);
int comChar(char str[], const char *delim);
int _get_numb(const char *s);
char *_strtok(char str[], const char *delim);

/* str3.c */
void _rvString(char *s);

/* check_Synx_err.c */
int _reaptChar(char *input, int i);
int index_Char(char *input, int *i);
int err_find_synx(char *input, int i, char last);
int check_Synx_err(data_shell *datash, char *input);
void printSynx_err(data_shell *datash, char *input, int i, int bool);

/* shellLoop.c */
char *rm_comments(char *in);
void shllLoop(data_shell *datash);

/* read_line.c */
char *readLine(int *i_eof);

/* splitz.c */
void addNode_s(sep_list **head_s, line_list **head_l, char *input);
char *swpChar(char *input, int bool);
void goToNext(sep_list **list_s, line_list **list_l, data_shell *datash);
char **slice_Line(char *input);
int slice_cmds(data_shell *datash, char *input);

/* rep_var.c */
void checkEnv_(r_var **h, char *in, data_shell *data);
int check_vars(r_var **h, char *in, char *st, data_shell *data);
char *rplce_input(r_var **head, char *input, char *new_input, int nlen);
char *rplce_var(char *input, data_shell *datash);

/* get_line.c */
ssize_t _getLine(char **lineptr, size_t *n, FILE *stream);
void asignLine(char **lineptr, size_t *n, char *buffer, size_t j);

/* exec_line */
int exec_line(data_shell *datash);

/* cmdExec.c */
int _isCdir(char *path, int *i);
char *_whichCmd(char *cmd, char **_environ);
int _excutble(data_shell *datash);
int _exec_cmd(data_shell *datash);
int _chk_err_cmd(char *dir, data_shell *datash);

/* env0.c */
char *_get_env_var(const char *name, char **_environ);
int _Env_(data_shell *datash);

/* env1.c */
void _setEnv(char *name, char *value, data_shell *datash);
char *cpy_info(char *name, char *value);
int _setEnvi(data_shell *datash);
int _unsetEnvi(data_shell *datash);

/* cd1.c */
void cd_Dot(data_shell *datash);
void cd_Tot(data_shell *datash);
void cd_To_Home(data_shell *datash);
void cd_prev(data_shell *datash);

/* sdShell.c */
int cd_Main(data_shell *datash);

/* getBuiltin */
int (*get_builtin(char *cmd))(data_shell *datash);

/* _exit.c */
int exit_Sh(data_shell *datash);

/* stdlib.c */
int get_length(int n);
int aToii(char *s);
char *sfj_itoa(int n);

/* error1.c */
char *errmsg_strcat(data_shell *, char *, char *, char *);
char *errmsg_notFound(data_shell *datash);
char *errmsg_get_cd(data_shell *datash);
char *errmsg_exit_sh(data_shell *datash);

/* error2.c */
char *error_get_alias(char **args);
char *errmsg_env(data_shell *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *errmsg_path_denied(data_shell *datash);


/* getError.c */
int get_error(data_shell *datash, int eval);

/* getSigint.c */
void _get_signal(int sig);

/* helper1.c */
void sfj_hlp_gen(void);
void sfj_hlp_env(void);
void sfj_hlp_setenv(void);
void sfj_hlp_unsetenv(void);
void sfj_hlp_exit(void);

/* helper2.c */
void sfj_hlp(void);
void sfj_hlp_cd(void);
void sfj_hlp_alias(void);

/* getHelp.c */
int get_help(data_shell *datash);

#endif
