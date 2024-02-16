/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:37:25 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/15 16:39:58 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	ft_command_fail(t_pipex *pipex)
{
	char	*msg;

	if (!pipex->child_args[0])
		write(STDERR_FILENO, "pipex: command not found: ''\n", 29);
	else
	{
		msg = ft_strjoin3("pipex: command not found: ", pipex->child_args[0], "\n");
		if (!msg)//may need to set malloc error here
			write(STDERR_FILENO, "pipex: command not found\n", 25);
		else
		{
			write(STDERR_FILENO, msg, ft_strlen(msg));
			free(msg);
		}
	}
	ft_freetable(pipex->child_args);
	ft_freetable(pipex->paths);
	free(pipex->pwd_origin);
	exit(FILENOTFOUND);
}

void	ft_parse_fail(t_pipex *pipex)
{
	write(STDERR_FILENO, "pipex: malloc failed: child_args\n", 33);
	ft_freetable(pipex->paths);
	free(pipex->pwd_origin);
	exit(EXIT_FAILURE);
}

void	ft_byedoc(t_pipex *pipex)
{
	char	*msg;

	msg = ft_strjoin3 //triggered on ctrl D?
		("pipex: warning: here-document delimited by end-of-file (wanted `",
			pipex->args[2], "')\n");
	if (!msg)//may need to set malloc error here
		write(STDERR_FILENO, "warning: here-doc delimited by end-of-file\n",
			25);
	else
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		free(msg);
	}
	ft_freetable(pipex->paths);
	free(pipex->pwd_origin);
	exit(EXIT_FAILURE);
}

void	ft_open_fail(t_pipex *pipex)
{
	ft_freetable(pipex->child_args);
	ft_freetable(pipex->paths);
	free(pipex->pwd_origin);
	exit(EXIT_FAILURE);
}

void	ft_dup2_fail(t_pipex *pipex)
{
	ft_freetable(pipex->child_args);
	ft_freetable(pipex->paths);
	free(pipex->pwd_origin);
	exit(EXIT_FAILURE);
}

void	ft_pipe_fail(t_pipex *pipex)
{
	write(STDERR_FILENO, "pipex: pipe failed\n", 19);
	ft_freetable(pipex->paths);
	free(pipex->pwd_origin);
	exit(EXIT_FAILURE);
}

void	ft_fork_fail(t_pipex *pipex)
{
	write(STDERR_FILENO, "pipex: fork failed\n", 19);
	ft_freetable(pipex->paths);
	free(pipex->pwd_origin);
	exit(EXIT_FAILURE);
}