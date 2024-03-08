/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:51:20 by kcouchma          #+#    #+#             */
/*   Updated: 2024/03/08 17:25:55 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	_exit_sigint(t_pipex *pipex, char **line, char *temp_i)
{
	if (pipex->hd_temp_fd != -1)
		close(pipex->hd_temp_fd);
	free (*line);
	*line = NULL;
	pipex->hd_temp_fd = open(temp_i, O_RDWR | O_TRUNC | O_CREAT, 0644);
	return (EXIT_SIGINT);
}

static int	_hd_break(char *linecpy, t_args *temp, int i)
{
	int	cpy_len;

	cpy_len = ft_strlen(linecpy);
	if (linecpy[cpy_len - 1] == '\n')
		linecpy[cpy_len - 1] = '\0';
	if (ft_strcmp(linecpy, temp->input_files[i]) == 0)
	{
		free(linecpy);
		return (1);
	}
	free(linecpy);
	return (0);
}

static int	_hd_read(t_pipex *pipex, t_args **temp, char *temp_i, int i)
{
	char	*line;
	char	*line_cpy;

	line = NULL;
	while (1)
	{
		write(STDERR_FILENO, "> ", 2);
		line = gnl(STDIN_FILENO);
		if (g_signal == EXIT_SIGINT)
			return (_exit_sigint(pipex, &line, temp_i));
		if (!line)
			return (ft_byedoc(pipex, *temp, EXIT_SUCCESS));
		line_cpy = ft_strdup(line);
		if (_hd_break(line_cpy, *temp, i) == 1)
			break ;
		write(pipex->hd_temp_fd, line, ft_strlen(line));
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

int	ft_heredoc(t_pipex *pipex, t_args **temp, int i, int arg_num)
{
	char	*char_argnum;
	char	*temp_name;
	int		hd_read_out;

	hd_read_out = 0;
	char_argnum = ft_itoa(arg_num);
	if (!char_argnum)
		return (EXIT_FAILURE);
	temp_name = ft_strjoin("./Pipex/temp_", char_argnum);
	if (!temp_name)
		return (_exit_fail(&char_argnum, &temp_name));
	if ((*temp)->input)
		free((*temp)->input);
	if ((*temp)->input)
		(*temp)->input = NULL;
	(*temp)->input = temp_name;
	pipex->hd_temp_fd = open(temp_name, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (pipex->hd_temp_fd == -1)
		return (_exit_fail(&char_argnum, &temp_name));
	hd_read_out = _hd_read(pipex, temp, temp_name, i);
	free(char_argnum);
	if (pipex->hd_temp_fd != -1)
		close(pipex->hd_temp_fd);
	signal(SIGINT, &sigint_handler);
	return (hd_read_out);
}
