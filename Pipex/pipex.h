/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:17:48 by kcouchma          #+#    #+#             */
/*   Updated: 2024/03/06 09:29:26 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

# define NOTHING -1 //there is no error and no commands
# define SYNTAX_ERROR 2
# define MALLOC_ERROR 12 //ENOMEM
# define BUILTIN_ERROR 42 //the builtin doesn't respect the subject
# define FILENOTFOUND 127 //command doesn’t exist, or isn’t in $PATH.
# define EXIT_SIGINT 130 //SIGINT triggered closure
# define EXIT_SIGQUIT 131 //SIGQUIT triggered closure
# define GNL_BUFFER_SIZE 1

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
/* gnl.c                                                                      */
/******************************************************************************/

/**
 * @brief Simple version of get_next_line, returns a line read from a file 
 * descriptor. Can only handle one fd at a time.
 * @param fd The file descriptor to read from.
 * @return char * The line that was read or NULL if there is nothing else 
 * to read, or an error occurred, or ctrl+C (SIGINT) was intercepted.
 */
char	*gnl(int fd);

/******************************************************************************/
/* heredocs.c                                                                 */
/******************************************************************************/

/**
 * @brief Handles the generation of heredoc temp files. One is created for each
 * present in the args_list list input files cases. 
 * Within _hd_read, gnl is called to read the line into the heredoc temp file.
 * ctrl C = EXIT_SIGINT (130).
 * ctrl D = EXIT_SUCCESS (0).
 * 
 * @param pipex pipex structure
 * @param temp current redirection filename (EOF limiter for the heredoc) 
 * within input_files of the current args_list node.
 * @param i current redirection number within input_files of the current 
 * args_list node.
 * @return int exit code of _hd_read()
 */
int		ft_heredoc(t_pipex *pipex, t_args **temp, int i);

/******************************************************************************/
/* pipex_cmds.c                                                               */
/******************************************************************************/

/**
 * @brief Creates the relevant redirections for child process inputs.
 * If present, the unused end of the pipe is closed. If there is a redirection
 * present in main->args_list->input, it is prioritised over the pipe (as bash).
 * @param pipex pipex structure
 * @param arg current node from args_list
 * @param main main structure
 * @param ired boolean :
 * 0 = first command position = 
 * no redirection if there is no redirection in the command structure
 * 1 = last/mid command position = 
 * redirection to/from pipe if there is no redirection in the command structure
 */
void	ft_input(t_pipex *pipex, t_args *arg, t_struct *main, int ired);

/**
 * @brief Creates the relevant redirections for child process outputs.
 * If present, the unused end of the pipe is closed. If there is a redirection
 * present in main->args_list->output, it is prioritised over the pipe (as bash)
 * @param pipex pipex structure
 * @param arg current node from args_list
 * @param main main structure
 * @param ired boolean :
 * 0 = first command position = 
 * no redirection if there is no redirection in the command structure
 * 1 = last/mid command position = 
 * redirection to/from pipe if there is no redirection in the command structure
 */
void	ft_output(t_pipex *pipex, t_args *arg, t_struct *main, int ored);

/**
 * @brief Not super-optimised fusion of two functions. Sets the 
 * input/output redirection (red) patterns for ft_input and ft_output.
 * Handles : single command (00), and final (10), first (01) and middle (11) 
 * commands in a pipeline.
 * @param pipex pipex structure
 * @param arg current node from args_list
 * @param main main structure
 * @param i current command position in the pipeline: 
 * i = 0 single / final command; 
 * i == main->common.nb_commands - 1 last command; 
 * otherwise middle.
 */
void	ft_cmd(t_pipex *pipex, t_args *arg, t_struct *main, int i);

/**
 * @brief Function launched in a while loop (where i is the number of input
 * arguments) to fork child processes.
 * Commands from the current args_list node are fed into the child processes 
 * If there is no command present then the process is exited with EXIT_SUCCESS
 * (see bash).
 * Input/output redirections are handled via ft_cmd (last pipeline command 
 * first).
 * ft_execve is then called to iterate through the paths, find the
 * function and replace the child process with the called function (or builtin).
 * If this fails, then ft_execve returns and the ft_builtin or ft_command_fail 
 * function is called to exit the child process.
 * In the parent process, current fd for the write end of the pipe created
 * in this fork is saved to pass to the next forked process so that it can 
 * provide input to this process (commands are created in reverse order).
 * If there is already a previously saved fd (ie this is not the first fork),
 * then it is closed before being replaced to prevent fd leaks.
 * @param pipex pipex structure
 * @param i command number (counting baskwards from end of pipeline)
 * @param arg current node from args_list
 * @param main main structure
 */
void	ft_forkchild(t_pipex *pipex, int i, t_args *arg, t_struct *main);

/******************************************************************************/
/* pipex_exits.c                                                              */
/******************************************************************************/

/**
 * @brief Handles the case where the input command (created from 
 * pipex->paths + args_list->command_name) is not found.
 * Calls the ft_write_join function to create the error message. The write 
 * function is used because it buffers to print to output. This prevents the 
 * output being scrambled if more than one command is not found (as the 
 * processes are running in parallel).
 * Relevant tables of tables are freed in ft_exit_error, and the program 
 * exited with a FILENOTFOUND (127) exit code.
 * @param pipex structure containing the (invalid) input command
 * @param arg current node in the linked list containing current command info
 * @param main pointer to the overall finishell structure
 */
void	ft_command_fail(t_pipex *pipex, t_args *arg, t_struct *main);

/**
 * @brief Called during the ft_heredoc function to 
 * handle the error when there is no input given to the terminal (ctrlD, 
 * buffer == NULL).
 * Calls the ft_write_join function to create the error message.
 * @param pipex structure containing the pipex->paths table to be freed.
 * @param arg current node in the linked list containing current command info
 * @param exit_code exit code to pass
 * @return int the designated exit code to pass
 */
int		ft_byedoc(t_pipex *pipex, t_args *arg, int exit_code);

/**
 * @brief Handles all other exits and failures (fatal and otherwise) within 
 * executing. Open, malloc, dup2 etc.
 * Calls unlink_hds to clean up heredoc temp files.
 * @param pipex pipex structure containing the pipex->paths table to be freed.
 * @param main main structure to be freed in child processes.
 * @param exit_code exit code to be passed
 * @return int exit_code can be replaced in the case where errno = ENOMEM
 */
int		ft_pipex_error(t_pipex *pipex, t_struct *main, int exit_code);

/**
 * @brief Unlinks temp heredoc files "temp_n" (stored in ./Pipex for the 
 * duration of the function). Removes "temp_0" up to "temp_1024".
 * @return int to pass SUCCESS/ENOMEM exit codes.
 */
int		unlink_hds(void);

/******************************************************************************/
/* pipex.utils.c                                                              */
/******************************************************************************/

/**
 * @brief Extracts the PATH variables to trace binary locations. Is exracted 
 * from main->common.f_envp into a table of tables stored at pipex->paths. 
 * Paths are separated using this delimiter : $PATH
 * If envp is empty (env -i command or missing variables), then the program will
 * create the paths output containing one string of '.' therefore searching
 * for a local exe.
 * @param envp environmental variables from main main->common.f_envp
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
 * @brief Execve with a shunt for builtin commands (to builtins_executing).
 * Calls execve to replace the current process if found in 'paths'. 
 * Constructs cmd_path using the paths in pipex->paths joined with the current
 * arg->command_table.
 * If the command starts with a '.' or '/', indicating that the command is 
 * either located in the current folder, or that the input command already 
 * includes the full path to the relevant command, then the function does not
 * use the envp-derived 'paths', and just uses the first argument of 
 * pipex.arg as a full command path.
 * If execve is successful, the process is replaced. If not, the current 
 * command path string is freed, and the next one is constructed and tested.
 * @param pipex pipex structure
 * @param child_arg pointer to current node in args_list
 * @param main main structure
 */
void	ft_execve(t_pipex *pipex, t_args *child_arg, t_struct *main);

/**
 * @brief Ensures the parent process waits for all child processes to terminate
 * before returning. To generate the exit code for executing, waitpid fills in 
 * the exit code of the first child (final command in the pipeline).
 * For the other processes, creates a wait(NULL) to catch their return in any
 * order.
 * @param pipex structure containing the number of commands (pipex->commands)
 * and the int to store the exit code (pipex->exit_code)
 */
void	ft_wait_parent(t_pipex *pipex, int nb_commands);

/******************************************************************************/
/* pipex.c                                                                    */
/******************************************************************************/

/**
 * @brief Handles SIGINT and SIGQUIT whilst in a child process. Sets the global
 * variable to 130/131 to serve as an exit code.
 * Newline triggers a redisplay of the finishell prompt.
 * @param signal input signal
 */
void	sig_handler_child(int signal);

/**
 * @brief Runs a loop to create a pipe (except for the last command), 
 * then fork the child process (ft_bonus_forkchild) for the length of the 
 * linked list main->args_list.
 * The write end is needed to reset pipex.temp_fd_out for use in each
 * child process, and is closed in ft_bonus_forkchild.
 * The parent then waits for the correct number of processes to terminate, and
 * stocks the exit code of the last command process (ft_wait_parent).
 * @param pipex pipex structure
 * @param main main structure
 */
void	ft_pipex(t_pipex *pipex, t_struct *main);

/**
 * @brief Initialises a number of variables in the pipex structure. 
 * The command paths are extracted from main->common.f_envp (ft_extract_paths).
 * @param pipex Structure to initialise.
 * @return int EXIT_SUCCESS/FAILURE in the case or malloc failure
 */
int		ft_pipex_init(t_pipex *pipex, t_struct *main);

/**
 * @brief Runs ft_pipex_init to initialises a number of variables in the pipex 
 * structure.
 * Runs ft_redirections to run through the input/output redirections and set 
 * args_list->input and output if present.
 * Checks for the correct number of input arguments - quits with an 
 * EXIT_SUCCESS (see bash) if there are no commands.
 * Filters the cases where a builtin needs to run in the parent process 
 * (eg cd, export with arguments to add to f_envp...)
 * Launches all other cases in a forked pipeline.
 * Resets sighandler, frees everything, returns exit code as in bash.
 * @param main main finishell structure
 * @return int returns exit code - either SUCCESS/FAILURE/ENOMEM or if a 
 * pipeline is launched, then the exit code of the final command (see bash)
 */
int		executing(t_struct *main);

/******************************************************************************/
/* redirections.c                                                             */
/******************************************************************************/

/**
 * @brief Handles the open/close of input files. Sets (and if present, 
 * overwrites) the final input file in args_list->input.
*/
// static int	_red_inputs_open(t_args *temp, int i);

/**
 * @brief Handles the inputs, looping through the args_list->input_redirs table.
 * Launches _red_inputs_open in the case of <, and ft_heredoc in the case of <<
 */
// static int	_red_inputs(t_pipex *pipex, t_args *temp);

/**
 * @brief Handles the outputs, looping through the args_list->output_redirs 
 * table.
 * In the case of > : opens, creates if absent, overwrites if present
 * In the case of >> : opens, creates if absent, appends if present
 * Files are then closed as only the last in the list will be used in pipex
 * The flag temp->output_type is set to 0/1 to send to pipex so the final 
 * redirections are correct
 */
// static int	_red_outputs(t_args *temp, int *i);

/**
 * @brief Handles inputs and outputs, looping through the args_list list.
 * The final output file for each argument is updated here (if present).
 * Creates a temp file 'temp' to hold user input, and stocks the fd in 
 * pipex->infile_fd.
 * @param pipex pipex structure
 * @param main main structure
 * @return int exit code (EXIT_SUCCESS/FAILURE)
 */
int		ft_redirections(t_pipex *pipex, t_struct *main);

#endif