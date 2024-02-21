/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:37:25 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/21 15:29:11 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	ft_free_pipex(t_pipex *pipex)
// {
// 	// if (pipex->infile)
// 	// 	free(pipex->infile);
// 	// if (pipex->outfile)
// 	// 	free(pipex->outfile);
// 	ft_freetable(pipex->paths);
// }

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
		write(STDERR_FILENO, "finishell: command not found: ''\n", 33);
	else
	{
		msg = ft_strjoin3("\x1b[38;2;255;0;0;1mfinishell 🤬: command not found: ", child_args->command_name, "\e[0m\n");
		if (!msg)//may need to set malloc error here
			write(STDERR_FILENO, "finishell: command not found\n", 29);
		else
		{
			write(STDERR_FILENO, msg, ft_strlen(msg));
			free(msg);
		}
	}
	ft_freetable(pipex->paths);
	ft_structclear(&main->args_list);
	free_envp(main->common.envp);
	exit(FILENOTFOUND);
}

void	ft_byedoc(t_pipex *pipex, t_args *child_args)
{
	char	*msg;

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

//open fail needs to return, not exit to handle the open fails in redirections

void	ft_fatal_child(t_pipex *pipex, t_struct *main)
{
	ft_freetable(pipex->paths);
	ft_structclear(&main->args_list);
	free_envp(main->common.envp);
	exit(EXIT_FAILURE);
}

int	ft_fatal_parent(t_pipex *pipex, t_struct *main)
{
	(void)main; //remove or use
	ft_freetable(pipex->paths);
	return (EXIT_FAILURE);
}

int	ft_open_fail(t_pipex *pipex, t_struct *main)
{
	(void)main; //remove or use
	ft_freetable(pipex->paths);
	if (pipex->pid == 0)
		exit(EXIT_FAILURE);
	return (EXIT_FAILURE);
}