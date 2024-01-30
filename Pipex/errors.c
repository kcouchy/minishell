/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:37:25 by kcouchma          #+#    #+#             */
/*   Updated: 2024/01/26 12:26:00 by kcouchma         ###   ########.fr       */
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

	msg = ft_strjoin3("pipex: command not found: ", pipex->child_args[0], "\n");
	if (!msg)
		write(STDERR_FILENO, "pipex: command not found\n", 25);
	else
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		free(msg);
	}
	ft_freetable(pipex->child_args);
	ft_freetable(pipex->paths);
	if (pipex->outfile_fd != -1)
		close(pipex->outfile_fd);
	if (pipex->infile_fd != -1)
		close(pipex->infile_fd);
	exit(EXIT_FAILURE);
}

void	ft_parse_fail(t_pipex *pipex)
{
	write(STDERR_FILENO, "pipex: cmd parse failure", 24);
	ft_freetable(pipex->paths);
	exit(EXIT_FAILURE);
}

void	ft_byedoc(t_pipex *pipex)
{
	char	*msg;

	msg = ft_strjoin3
		("pipex: warning: here-document delimited by end-of-file (wanted `",
			pipex->args[2], "')\n");
	if (!msg)
		write(STDERR_FILENO, "warning: here-doc delimited by end-of-file\n",
			25);
	else
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		free(msg);
	}
	ft_freetable(pipex->paths);
	exit(EXIT_FAILURE);
}

void	ft_input_fail(t_pipex *pipex)
{
	perror("failed to create input file");
	ft_freetable(pipex->paths);
	exit(EXIT_FAILURE);
}
