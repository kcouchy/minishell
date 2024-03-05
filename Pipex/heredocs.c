/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:51:20 by kcouchma          #+#    #+#             */
/*   Updated: 2024/03/05 12:18:56 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	_exit_sigint(t_pipex *pipex, char **line, char *temp_i)
{
	close(pipex->hd_temp_fd);
	free (*line);
	*line = NULL;
	pipex->hd_temp_fd = open(temp_i, O_RDWR | O_TRUNC | O_CREAT, 0644);
	return (EXIT_SIGINT);
}

static int	_hd_read(t_pipex *pipex, t_args **temp, char *temp_i, int i)
{
	char	*line;

	line = NULL;
	while (1)
	{
		write(STDERR_FILENO, "> ", 2);
		line = gnl(STDIN_FILENO);
		if (g_signal == EXIT_SIGINT)
			return (_exit_sigint(pipex, &line, temp_i));
		if (!line)
			return (ft_byedoc(pipex, *temp, EXIT_SUCCESS));
		else if (ft_strncmp(line, "\n", 1) != 0)
			if (ft_strncmp(line, (*temp)->input_files[i],
					(ft_strlen(line) - 1)) == 0)
				break ;
		write(pipex->hd_temp_fd, line, ft_strlen(line));
		if (!(*temp)->input_files[i][0] && ft_strncmp(line, "\n", 1) == 0)
			break ;
		free(line);
	}
	free(line);
	return (EXIT_SUCCESS);
}

static int	_exit_fail(char **char_i, char **temp_i)
{
	if (*char_i)
	{
		free(*char_i);
		*char_i = NULL;
	}
	if (*temp_i)
	{
		free(*temp_i);
		*temp_i = NULL;
	}
	if (errno == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (EXIT_FAILURE);
}

int	ft_heredoc(t_pipex *pipex, t_args **temp, int i)
{
	char	*char_i;
	char	*temp_i;
	int		hd_read_out;

	hd_read_out = 0;
	char_i = ft_itoa(i);
	if (!char_i)
		return (EXIT_FAILURE);
	temp_i = ft_strjoin("./Pipex/temp_", char_i);
	if (!temp_i)
		return (_exit_fail(&char_i, &temp_i));
	if ((*temp)->input)
		free((*temp)->input);
	if ((*temp)->input)
		(*temp)->input = NULL;
	(*temp)->input = temp_i;
	pipex->hd_temp_fd = open(temp_i, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (pipex->hd_temp_fd == -1)
		return (_exit_fail(&char_i, &temp_i));
	hd_read_out = _hd_read(pipex, temp, temp_i, i);
	free(char_i);
	close(pipex->hd_temp_fd);
	signal(SIGINT, &sigint_handler);
	return (hd_read_out);
}
