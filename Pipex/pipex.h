/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:17:48 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/20 16:06:11 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

//# define FILENOTFOUND 127
# define FILENOTFOUND 127 //command doesn’t exist, or isn’t in $PATH.

/******************************************************************************/
/* Includes                                                                   */
/******************************************************************************/

# include <stdlib.h>		/*malloc/free/exit*/
# include <fcntl.h>			/*open*/
# include <unistd.h>		/*close/read/write/fork/pipe*/
# include <string.h>		/*dup/dup2/execve*/
# include <stdio.h>			/*perror*/
# include <sys/wait.h>		/*wait/waitpid*/
# include "libft/libft.h"	/*includes my libft.h - ft_printf etc.*/
# include "./../minishell.h"	/*minishell (parsing, t_struct, t_args)*/

/******************************************************************************/
/* Structures                                                                 */
/******************************************************************************/

typedef struct s_pipex_list
{
	// int				heredoc;		//boolean to handle heredoc input
	int				pipe_fd[2];		//holds pipe fds: [0] = read, [1] = write
	int				temp_fd_out;	//holds write fd between forks (forkchild)
	// int				commands;		//no. of commands
	// char			**args;			//all command structures (argv)
	// char			**child_args;	//all parts of a single command
	int				pid;			//current fork id
	int				pid_last;		//pid of last (1st made) command to return
	int				exit_code;		//of last command to return in parent
	char			*infile;		//final input redirection
	// int				infile_fd;		//input file fd for heredoc version
	int				outfile_type;	//0 = trunc, 1 = append
	char			*outfile;		//final output redirection (heredoc or no)
	// char			**envp;			//envp input
	char			**paths;		//paths separated from envp PATH variable
	// char			*pwd_origin;	//pwd at launch for backup in builtins
}					t_pipex;

/******************************************************************************/
/* utils.c                                                                    */
/******************************************************************************/

/**
 * @brief Extracts the PATH variables from the environmental variables (from 
 * envp in main) into a table of tables. Each path (delineated by : in envp) is
 * put into a string table in the output `paths`.
 * If envp is empty (env -i command or missing variables), then the program will
 * make create the paths output containing one string of '.' therefore searching
 * for a local exe.
 * @param envp system environmental variables from main envp
 * @return char** table of tables of each of the paths present in PATH
 */
char	**ft_extract_paths(char **envp);

/**
 * @brief Adaptation of the ft_strjoin function, to accept three string inputs:
 * will malloc, concatenate, and null-terminate the joined 'output' string.
 * None of the input strings are freed in this function.
 * @param s1 first string
 * @param s2 second string
 * @param s3 third string
 * @return char* malloc'd null-terminated concatenation of s1-s3.
 */
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);

/**
 * @brief Calls execve to replace the current process if found in 'paths'. Takes
 * each path from the 'paths' table of tables (from ft_extract_paths), appends 
 * the name of the command (from pipex.child_args) to the end (with ft_strjoin3)
 * to create the full command path 'cmd_path'.
 * If execve is successful, the process is replaced. If not, the current 
 * command path string is freed, and the next one is constructed and tested.
 * If the command starts with a '.' or '/', indicating that the command is 
 * either located in the current folder, or that the input command already 
 * includes the full path to the relevant command, then the function does not
 * use the envp-derived 'paths', and just uses the first argument of 
 * pipex.child_args as a full command path.
 * @param pipex structure containing pipex->child_args, pipex->paths and 
 * pipex->envp for the execve command.
 */
void	ft_execve(t_pipex *pipex, t_args *args_list, char **envp);

/******************************************************************************/
/* errors.c                                                                   */
/******************************************************************************/

void	ft_free_pipex(t_pipex *pipex);

/**
 * @brief If the pointer to the table of tables is not NULL, frees each member 
 * of the input table of tables, then the table itself.
 * @param table input table of tables to be freed.
 */
void	ft_freetable(char **table);

/**
 * @brief Handles the case where the input command (created from 
 * pipex->paths + pipex->child_args) is not found. Recreates the bash message
 * zsh : command not found: cmd. 
 * First the output is redirected to the terminal using the unmodified stderr 
 * output (fd = 2). The write function is used because it buffers to print to 
 * output. This prevents the output being scrambled if more than one command is 
 * not found (as the processes are running in parallel). ft_printf is then used 
 * o print the (invalid) command name only.
 * Relevant tables of tables are freed, and the program exited with a FAILURE.
 * @param pipex structure containing the (invalid) input command 
 * (pipex->child_args[0]), and the tables to be freed:
 * (pipex->paths + pipex->child_args)
 */
void	ft_command_fail(t_pipex *pipex, t_args *child_args, t_struct *main);

/**
 * @brief Here because norminette. Called during the ft_heredoc function to 
 * handle the error when there is no input given to the terminal (ctrlD, 
 * buffer == NULL).
 * ft_printf used to replicate bash error message for the same case.
 * @param pipex structure containing the pipex->paths table to be freed.
 */
void	ft_byedoc(t_pipex *pipex, t_args *child_args);

/**
 * @brief Here because norminette. Called in ft_heredoc to handle the case 
 * where the open command for the temp file fails.
 * @param pipex structure containing the pipex->paths table to be freed.
 */
void	ft_open_fail(t_pipex *pipex);

void	ft_dup2_fail(t_pipex *pipex);

void	ft_pipe_fail(t_pipex *pipex);

void	ft_fork_fail(t_pipex *pipex);

/******************************************************************************/
/* bonus_cmds.c                                                               */
/******************************************************************************/

void	ft_inputs(t_pipex *pipex);

void	ft_outputs(t_pipex *pipex);

/**
 * @brief Identical to base program except for the heredoc case.
 * Creates the relevant redirections in the child that will run the last
 * command in the series (this is the first to be created).
 * The unused write end of the pipe is closed.
 * The read end of the pipe is duplicated to replace the standard input, and 
 * the original closed.
 * In the heredoc case, the output file is opened with the following flags 
 * (fd stocked in out_fd):
 * O_WRONLY, 0644 : write-only (permissions 644)
 * O_APPEND : append (new info will be appended to contents if the file exists)
 * O_CREAT : file will be created if it does not already exist.
 * In the normal bonus case, the output file is opened similarly except:
 * O_TRUNC : truncated (will overwrite all contents if the file exists)
 * The fd of the output file is then duped to replace the standard output.
 * @param pipex structure containing the tables to be freed in case of error
 * (pipex->paths + pipex->child_args)
 */
void	ft_bonus_last_cmd(t_pipex *pipex);

/**
 * @brief Identical to base program except for the heredoc case.
 * Creates the relevant redirections in the child that will run the first
 * command in the series (this is the last to be created).
 * The unused read end of the pipe is closed.
 * The write end of the pipe is duplicated to replace the standard output, and 
 * the original closed.
 * The input file is opened with the following flags (fd stocked in in_fd):
 * O_RDONLY : read-only
 * In the heredoc case, the temp file is used, otherwise the name of the input
 * file given in the command is used. Thft_pipe_fail(t_pipex *pipex)
 */
void	ft_bonus_first_cmd(t_pipex *pipex);

/**
 * @brief Not present in base program.
 * Handles all commands that come between the first and last commands in the 
 * chain (they all read and write from/to pipes and are thus identical).
 * Closes the unused write end of the pipe.
 * The write end of the pipe is retrieved from temp file containing the write 
 * end of the pipe created in the previous command's fork (because the pipe_fd 
 * in the structure is overwritten with the new pipe, and this process needs to 
 * write to the previous fork's input). This is then duped to replace the 
 * standard output, and the original closed.
 * The read end of the new pipe is duplicated to replace the standard input, 
 * and the original closed.
 * @param pipex 
 */
void	ft_bonus_mid_cmd(t_pipex *pipex);

/**
 * @brief Function launched in a while loop (where i is the number of input
 * arguments). The parent process is forked in the child process 
 * (pipex->pid == 0), the table of tables containing the arguments for each 
 * child function is created using ft_split. The arguments are fed into the 
 * child processes in reverse order (last command first), the heredoc boolean
 * is used to correct for the change in argv number in the here_doc bonus case.
 * Depending on the number of the commands, the relevant ft_n_cmd is called to 
 * handle the file descriptor redirections.
 * The ft_execve function is then called to iterate through the paths, find the
 * function and replace the child process with the called function.
 * If this fails, the ft_command_fail function is called, and the child process
 * is exited with the error 'pipex: command not found: cmd' and EXIT_FAILURE.
 * In the parent process, current fd for the write end of the pipe created
 * in this fork is saved to pass to the next forked process so that it can 
 * provide input to this process (commands are created in reverse order).
 * If there is already a previously saved fd (ie this is not the first fork),
 * then it is closed before being replaced to prevent fd leaks.
 * @param pipex structure containing the number of input commands 
 * (pipex->commands), pipex->pid to stock the current fork pid, and the tables 
 * to be freed in case of error (pipex->paths + pipex->child_args).
 * @param i input argument counter
 */
void	ft_bonus_forkchild(t_pipex *pipex, int i, t_args *child_args, t_struct *main);

/**
 * @brief Creates a wait(NULL) for each of the child processes 
 * (n = pipex->commands), to ensure that the parent waits for each process to 
 * return before terminating.
 * @param pipex structure containing the number of commands (pipex->commands)
 */
void	ft_wait_parent(t_pipex *pipex, int nb_commands);

/******************************************************************************/
/* bonus_pipex.c                                                              */
/******************************************************************************/

/**
 * @brief Runs a loop to create a pipe, then fork the child process 
 * (ft_bonus_forkchild) for i = the number of commands (pipex->commands).
 * In the parent, the unused read end of the pipe created in each loop is 
 * closed. The write end is needed to reset pipex.temp_fd_out for use in each
 * child process, and is closed in (ft_bonus_forkchild).
 * The parent then waits for the correct number of processes to terminate 
 * (ft_wait_parent).
 * @param pipex structure containing the number of input commands 
 * (pipex->commands), and the tables to be freed in case of error (pipex->paths 
 * + pipex->child_args).
 */
void	ft_bonus_pipex(t_pipex *pipex, t_struct *main);

/**
 * @brief Handles the reinitialisation of variables for the heredoc case.
 * Creates a temp file 'temp' to hold user input, and stocks the fd in 
 * pipex->infile_fd.
 * Using get_next_line, reads each line from the stdin and put it into the 
 * temp file until the line == the end of file tag LIMITER.
 * In the case where the program is exited without input (ctrlD : buffer == 0),
 * launches ft_byedoc to exit program.
 * Once writing is completed, temp file is closed (to be reopened in 
 * ft_bonus_first_cmd).
 * @param pipex 
 */
int		ft_heredoc(t_pipex *pipex, t_args *args_list, int i);

/**
 * @brief Initialises a number of variables in the pipex structure. 
 * The command paths are extracted from envp (ft_extract_paths).
 * @param pipex Structure to initialise.
 */
void	ft_pipex_init(t_pipex *pipex, t_struct *main);

/**
 * @brief Runs ft_pipex_init to initialises a number of variables in the pipex 
 * structure.
 * If the second argument (argv[1]) is "here_doc", reinitialise the structure 
 * in ft_heredoc to handle the heredoc bonus case.
 * Cheacks for the correct number of input arguments: there are more than 5 
 * input arguments (2 files, at least 2 command structures, and the exe name), 
 * or 6 in the here_doc case. Otherwise throws an error showing the correct 
 * input syntax. 
 * For the heredoc case, closes and unlinks the temp file holding the user 
 * input to the terminal, and frees the pipex.paths table of tables for all 
 * cases where the parent returns.
 * @param argc Number of input args
 * @param argv Table of tables containing the input strings
 * @param envp Table of tables containing the environmental variables (env)
 * @return int 0 if all is well.
 */
// int		executing(int argc, char **argv, char **envp, int num_args);
//int		executing(t_args *args, char **envp, int num_args);
int		executing(t_struct *main);

/******************************************************************************/
/* single_cmd.c                                                               */
/******************************************************************************/

void	ft_single_cmd(t_pipex *pipex, t_args *child_args, t_struct *main);

/******************************************************************************/
/* Builtins                                                                   */
/******************************************************************************/

int		ft_tablen(char **tab);

#endif