/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:37:25 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/20 16:43:22 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_pipex(t_pipex *pipex)
{
	if (pipex->infile)
		free(pipex->infile);
	if (pipex->outfile)
		free(pipex->outfile);
	ft_freetable(pipex->paths);
}

void	ft_freetable(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}

void	ft_command_fail(t_pipex *pipex, t_args *child_args, t_struct *main)
{
	char	*msg;

	if (!child_args->command_name)
		write(STDERR_FILENO, "pipex: command not found: ''\n", 29);
	else
	{
		msg = ft_strjoin3("\x1b[38;2;255;0;0;1mfinishell 🤬: command not found: ", child_args->command_name, "\n");
		if (!msg)//may need to set malloc error here
			write(STDERR_FILENO, "pipex: command not found\n", 25);
		else
		{
			write(STDERR_FILENO, msg, ft_strlen(msg));
			free(msg);
		}
	}
	ft_free_pipex(pipex);
	ft_structclear(&main->args_list);
	free_envp(main->common.envp);
	// free(pipex->pwd_origin);
	exit(FILENOTFOUND);
}

void	ft_byedoc(t_pipex *pipex, t_args *child_args) //also needs to be triggered on ctrl D?
{
	char	*msg;

	//triggered on ctrl D? - need to add limiter to input_files[0] in case of heredoc
	g_signal = 0;
	msg = ft_strjoin3 
		("\x1b[38;2;255;0;0;1mfinishell 🤬: warning: here-document delimited by end-of-file (wanted `",
			child_args->input_files[0], "')\n");
	if (!msg)//may need to set malloc error here
		write(STDERR_FILENO, "\x1b[38;2;255;0;0;1mfinishell 🤬: warning: here-doc delimited by end-of-file\n",
			25);
	else
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		free(msg);
	}
	pipex->exit_code = EXIT_FAILURE;
	return ;
}

// ----------------------------------
// Need to add frees here for the child processes
// 	ft_structclear(&main->args_list);
// 	free_envp(main->common.envp);

void	ft_open_fail(t_pipex *pipex)
{
	// ft_freetable(pipex->child_args);
	ft_free_pipex(pipex);
	// free(pipex->pwd_origin);
	// exit(EXIT_FAILURE);
	exit(EXIT_FAILURE);
}

void	ft_dup2_fail(t_pipex *pipex)
{
	// ft_freetable(pipex->child_args);
	ft_free_pipex(pipex);
	// free(pipex->pwd_origin);
	exit(EXIT_FAILURE);
}

void	ft_pipe_fail(t_pipex *pipex)
{
	write(STDERR_FILENO, "pipex: pipe failed\n", 19);
	ft_free_pipex(pipex);
	// free(pipex->pwd_origin);
	exit(EXIT_FAILURE);
}

void	ft_fork_fail(t_pipex *pipex)
{
	write(STDERR_FILENO, "pipex: fork failed\n", 19);
	ft_free_pipex(pipex);
	// free(pipex->pwd_origin);
	exit(EXIT_FAILURE);
}