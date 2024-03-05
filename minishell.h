/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:11:50 by lribette          #+#    #+#             */
/*   Updated: 2024/03/05 19:57:54 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/******************************************************************************/
/******************************************************************************/
/********************************** Headers ***********************************/
/******************************************************************************/
/******************************************************************************/

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "./Pipex/libft/libft.h"

/******************************************************************************/
/******************************************************************************/
/********************************* Variables **********************************/
/******************************************************************************/
/******************************************************************************/

# define RED "\x1b[38;2;255;0;0;1mfinishell 🤬:"
# define ORANGE "\x1b[38;2;255;113;0;1mfinishell ⚠️ :"
# define WR_CMD " command not found"
# define GREEN "\x1b[38;2;0;150;0;1m"
# define SHIT "\x1b[38;2;136;87;66;1mfinishell 💩:"
# define RESET "\e[0m"
# define MALLOC_ERROR 12 //ENOMEM

typedef struct s_pipex_list
{
	int				pipe_fd[2];		//holds pipe fds: [0] = read, [1] = write
	int				temp_fd_out;	//holds write fd between forks (forkchild)
	int				pid;			//current fork id
	int				pid_last;		//pid of last (1st made) command to return
	int				exit_code;		//of last command to return in parent
	char			**paths;		//paths separated from envp PATH variable
	int				hd_temp_fd;		//temp to pass between heredoc functions
}					t_pipex;

typedef enum e_type
{
	WORD = 1,
	SEPARATOR,
	COMMAND,
	OPTION,
	ARGUMENT,
	VARIABLE,
	PIPE,
	REDIRECTION,
	INPUT_REDIR,
	OUTPUT_REDIR,
	INPUT_FILE,
	OUTPUT_FILE,
	EQUAL
}	t_type;

/******************************************************************************/
/******************************************************************************/
/********************************** Globals ***********************************/
/******************************************************************************/
/******************************************************************************/

extern volatile int	g_signal;

/******************************************************************************/
/******************************************************************************/
/********************************* Structures *********************************/
/******************************************************************************/
/******************************************************************************/

typedef struct s_variables
{
	char	*str;
	char	*left;
	int		quote;
	int		is_there_a_variable;
}	t_variables;

typedef struct s_parsing
{
	int			argc;
	char		**argv;
	int			*types;
	int			number_of_commands;
	int			error;
	t_variables	var;
}	t_parsing;

typedef struct s_common
{
	int		nb_commands;
	char	**f_envp;
	char	*pwd;
}	t_common;

typedef struct s_args
{
	//echo -n bonjour | cat -e Makefile > test <salut
	char			*whole_cmd; //cat -e Makefile minishell.h > test
	char			**command_table; // cat ; -e ; Makefile ; minishell.h
	char			*command_name; //"\0" ; NULL ; cat
	char			**flags; //-e
	char			*args; //arguments : Makefile minishell.h
	char			**input_redirs; //< ; <<
	char			**input_files; //salut
	char			*input; //final input redirection
	char			**output_redirs; //> ; >>
	char			**output_files; //test
	char			*output; //final output redirection
	int				output_type; //0 = trunc, 1 = append
	int				is_builtin; //0 ; 1
	struct s_args	*next; //
}	t_args;

typedef struct s_struct
{
	t_parsing	parse;
	t_common	common;
	t_args		*args_list;
	int			exit_code;
}	t_struct;

/******************************************************************************/
/******************************************************************************/
/********************************** Builtins **********************************/
/******************************************************************************/
/******************************************************************************/

/* ************************************************************************** */
/* builtins_utils.c															  */
/* ************************************************************************** */

/**
 * @brief 
 * 
 * @param var 
 * @param main 
 * @return char* 
 */
char	*ex_fenvp(char *var, t_struct *main);

/**
 * @brief Checks in the whole parsing table if there is a builtin. 
 * If so, and the builtins found are either echo or exit, this will execute the
 * appropriate parsing function.
 * @param parse Structure indicating each token associated with its type.
 */
void	builtins_parsing(t_parsing *parse);

/**
 * @brief Checks which builtin the command_name is and executes the associated
 * function. If it doesn't match any of the conditions (respecting the
 * subject), arg->is_builtin is set to 2 and an error message is raised in
 * another function.
 * @param pipex Structure allowing execution of the execve command.
 * @param arg Current node in the linked list containing current command info.
 * @param main Pointer to the overall finishell structure.
 * @return int 
 */
int		builtins_executing(t_pipex *pipex, t_args *arg, t_struct *main);

/**
 * @brief If the builtin matches the subject, it sets the exit code to
 * EXIT_SUCCESS. Otherwise, it prints an error message and sets the exit code
 * to BUILTIN_ERROR. The program then exits with the correct exit code.
 * @param pipex Structure allowing execution of the execve command.
 * @param arg Current node in the linked list containing current command info.
 * @param main Pointer to the overall finishell structure.
 */
void	ft_builtin_fail(t_pipex *pipex, t_args *arg, t_struct *main);

/* ************************************************************************** */
/* cd.c																		  */
/* ************************************************************************** */

/**
 * @brief 
 * 
 * @param arg 
 * @param main 
 * @return int 
 */
int		ft_cd(t_args *arg, t_struct *main);

/* ************************************************************************** */
/* echo.c																	  */
/* ************************************************************************** */

/**
 * @brief Checks the flags according to the subject. If a flag contains a
 * character other than 'n', all the next flags and this one become arguments.
 * @param parse Structure indicating each token associated with its type.
 * @param i Index to the beginning of the command.
 * @return int 
 */
int		echo_parsing(t_parsing *parse, int i);

/**
 * @brief Prints all arguments of the echo command, and a '\n' if there is no
 * flag.
 * @param arg Current node in the linked list containing current command info.
 * @return int 
 */
int		ft_echo(t_args *arg);

/* ************************************************************************** */
/* env.c																	  */
/* ************************************************************************** */

/**
 * @brief 
 * 
 * @param main 
 * @return int 
 */
int		ft_env(t_struct *main);

/* ************************************************************************** */
/* exit.c																	  */
/* ************************************************************************** */

/**
 * @brief Changes all flags to arguments to handle negative numbers.
 * 
 * @param parse Structure indicating each token associated with its type.
 * @param i Index to the beginning of the command.
 * @return int 
 */
int		exit_parsing(t_parsing *parse, int i);

/**
 * @brief If we're in a parent process, it prints "exit". If exit has
 * arguments, the exit code is the first argument modulo 256. If the argument
 * contains a character or isn't between LLONG_MIN and LLONG_MAX, the exit code
 * is 2 (SYNTAX_ERROR). The process is then terminated cleanly.
 * @param pipex Structure allowing execution of the execve command.
 * @param main Pointer to the overall finishell structure.
 * @param arg Current node in the linked list containing current command info.
 */
void	ft_exit(t_pipex *pipex, t_struct *main, t_args *arg);

/* ************************************************************************** */
/* export_exec.c															  */
/* ************************************************************************** */

/**
 * @brief if export only, print all of envp to the terminal except the 
 * variable "_" and "?"
 * copy and sort envp, (and free at the end) 
 * then in loop add declare -x add "" around the string(after = and at the end)
 * if export (variable), then add "variable"+"="+"variable value" to env
 * if export (variable=value), then add "variable=value" to env
 * in both cases, overwrite variable if present, add if not
 */
int		ft_export(t_args *arg, t_struct *main);

/* ************************************************************************** */
/* export_parse.c															  */
/* ************************************************************************** */

/**
 * @brief Returns a double table containing only the command and arguments with
 * at least one equal symbol, one character and no whitespace. It prints an
 * error for each bad argument.
 * @param main Pointer to the overall finishell structure.
 * @param start Index to the beginning of the command.
 * @param end Index to the end of the command.
 * @return char** 
 */
char	**export_parsing(t_struct *main, int start, int end);

/* ************************************************************************** */
/* fenvp_utils.c															  */
/* ************************************************************************** */

/**
 * @brief 
 * 
 * @param tab 
 * @return int 
 */
int		ft_tablen(char **tab);

/**
 * @brief 
 * 
 * @param f_envp 
 * @return int 
 */
int		ft_find_eq(char *f_envp);

/**
 * @brief 
 * 
 * @param arg 
 * @param f_envp 
 * @return int 
 */
int		find_arg(char *arg, char **f_envp);

/**
 * @brief 
 * 
 * @param tab 
 * @return char** 
 */
char	**ft_realloc(char **tab);

/**
 * @brief 
 * 
 * @param arg 
 * @param f_envp 
 * @return int 
 */
int		ft_mod_fevnp(char *arg, char ***f_envp);

/* ************************************************************************** */
/* pwd.c																	  */
/* ************************************************************************** */

/**
 * @brief 
 * 
 * @param main 
 * @return int 
 */
int		ft_pwd(t_struct *main);

/* ************************************************************************** */
/* unset.c																	  */
/* ************************************************************************** */

/**
 * @brief For all arguments in arg->command_table, if there is an equal symbol,
 * it prints an error message. Otherwise, if it finds the environment variable
 * in f_envp that corresponds to the actual argument, it frees it. All the
 * following environment variables in f_envp are moved to the left.
 * @param arg Current node in the linked list containing current command info.
 * @param main Pointer to the overall finishell structure.
 * @return int 
 */
int		ft_unset(t_args *arg, t_struct *main);

/******************************************************************************/
/******************************************************************************/
/********************************** Parsing ***********************************/
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/*********************************** Lexing ***********************************/
/******************************************************************************/

/**
 * @brief Allocates two tables.
 * The first one is a char ** and stocks each word/separator.
 * The second is an int table and stocks enums associated with the words in the
 * other table on the same index.
 * _skip_to_quote(): If there is a quote, iterates i until there is a closing
 * quote and returns i. If there isn't, it prints an error and returns the end
 * of the string.
 * _count_tokens(): Counter is iterated every time there is a type change
 * (separator or word) or a space. The function will return the counter.
 * _create_lexer(): Skips the whitespaces, checks the type of what we want to
 * duplicate and duplicates it in what_type().
 * @param parse Structure indicating each token associated with its type.
 * @param input The string created by readline and then by check_variables().
 */
void	alloc_tables(t_parsing *parse, char *input);

/**
 * @brief Prints error messages to reproduce bash behaviour and changes the
 * type of each token to be more precise for further parsing.
 * which_redirection(): If the current token is an input, returns the input
 * enum. Otherwise, if it is an output, returns the output enum. Else,
 * returns 0 -> it's an error.
 * _file(): If the previous token was a redirection, checks which one
 * thanks to _which_redirection() and the current token must be a file with
 * the same input/output type as the redirection.
 * _not_separator(): If the current token is the first token of the command,
 * it becomes a command. Otherwise, if the first character of the token is
 * '-', it becomes an option. Else, it becomes an argument. The functions then
 * call _file() to change the token if the previous token was a redirection.
 * _separator(): Compares the current token with several types of separators
 * and prints an error if two separators are side by side.
 * @param parse Structure indicating each token associated with its type.
 */
void	check_commands(t_parsing *parse);

/**
 * @brief 
 * 
 * @param variables 
 * @param f_envp 
 * @param input 
 * @return char* 
 */
char	*check_variables(t_variables *variables, char **f_envp, char *input);

/******************************************************************************/
/*********************************** Autre ************************************/
/******************************************************************************/

/* ************************************************************************** */
/* utils.c																	  */
/* ************************************************************************** */
int		is_separator(char c);
int		is_space(char c);
int		is_quote(char c);
int		ft_strcmp(char *s1, char *s2);
void	is_argument_a_command(t_parsing *parse, int i);
char	*ft_strndup(char *s, int start, int end, char *returned);
char	*var_strdup(char *f_envp);
char	*var_strjoin(char *s1, char *s2);
void	ft_write_join(char *error_type, char *cmd, char *arg, char *str);
void	ft_exit_error(t_pipex *pipex, t_struct *main, int exit_code);

/* ******************** Lexing ******************** */
int		what_type(t_parsing *parse, char *input, int i, int separator);

/* ******************** Parsing ******************** */
char	*ft_argjoin(char *s1, char *s2);
void	fill_strings(t_args *cmd, t_struct *main, int start, int end);
char	**fill_type(int type, t_struct *main, int start, int end);
char	**fill_table(t_struct *main, int start, int end);
int		check_nothing(char *input);
int		is_heredoc(char *input, int i);
int		parsing(t_struct *main, char *input);

/* ************* Parsing to Executing ************** */
t_args	*parsing_to_executing(t_struct *main);

int		is_builtin(char *command);
char	**ch_exit_code(int exit_code, char **f_envp);

/******************************************************************************/
/******************************************************************************/
/********************************* Common Part ********************************/
/******************************************************************************/
/******************************************************************************/

/*ft_free.c*/
void	free_table(char **tab);
void	ft_free_parsing(t_parsing *parse);
void	ft_structclear(t_args **cmd);
char	*err_str(char *s1, char *s2, char *s3, char *s4);

/*minishell.c*/
/**
 * @brief 	rl_on_new_line();
 * 			//needed to reshow prompt
			rl_replace_line("", 1);
			//empties readline buffer in case there's something before the ^C
			rl_redisplay();
			//effectively forces the prompt to redisplay before you type
 * 
 * @param signal 
 */
void	sigint_handler(int signal);

#endif
