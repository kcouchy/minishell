/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:59:31 by kcouchma          #+#    #+#             */
/*   Updated: 2024/03/04 14:04:01 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	_hd_read(t_pipex *pipex, t_args **temp, char *temp_i, int i)
{
	char	*line;

	line = NULL;
	while (1)
	{
		write(STDERR_FILENO, "> ", 2);
		line = gnl(STDIN_FILENO);
		if (g_signal == EXIT_SIGINT)
		{
			(close(pipex->hd_temp_fd), free (line));
			pipex->hd_temp_fd = open(temp_i, O_RDWR | O_TRUNC | O_CREAT, 0644);
			return (EXIT_SIGINT);
		}
		if (!line)
			return (ft_byedoc(pipex, *temp, EXIT_SUCCESS)); //ctrl D = EXIT_SUCCESS. For malloc fail need to exit from inside gnl
		else if (ft_strncmp(line, "\n", 1) != 0)
			if (ft_strncmp(line, (*temp)->input_files[i],
					(ft_strlen(line) - 1)) == 0)
				break ;
		write(pipex->hd_temp_fd, line, ft_strlen(line));
		if (!(*temp)->input_files[i][0] && ft_strncmp(line, "\n", 1) == 0)
			break ;
		free(line);
	}
	return (free(line), EXIT_SUCCESS);
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
		free(char_i);
	if (!temp_i)
		return (EXIT_FAILURE);
	if ((*temp)->input)
		(free((*temp)->input), (*temp)->input = NULL);
	(*temp)->input = temp_i;
	pipex->hd_temp_fd = open(temp_i, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (pipex->hd_temp_fd == -1)
		(free(char_i), free(temp_i));
	if (pipex->hd_temp_fd == -1)
		return (EXIT_FAILURE);
	hd_read_out = _hd_read(pipex, temp, temp_i, i);
	(free(char_i), close(pipex->hd_temp_fd));
	signal(SIGINT, &sigint_handler);
	return (hd_read_out);
}

static int	_red_inputs(t_pipex *pipex, t_args *temp)
{
	int		fd;
	int		i;
	int		hd_out;

	fd = -1;
	i = -1;
	while (temp->input_files[++i])
	{
		fd = -1;
		if (ft_strcmp(temp->input_redirs[i], "<") == 0)
		{
			fd = open(temp->input_files[i], O_RDONLY);
			if (fd == -1)
				return (EXIT_FAILURE);
			close(fd);
			if (temp->input)
				(free(temp->input), temp->input = NULL);
			temp->input = ft_strdup(temp->input_files[i]);
			if (!temp->input)
				return (EXIT_FAILURE);
		}
		else if (ft_strcmp(temp->input_redirs[i], "<<") == 0)
		{
			hd_out = ft_heredoc(pipex, &temp, i);
			if (hd_out != EXIT_SUCCESS)
				return (hd_out);
		}
	}
	return (EXIT_SUCCESS);
}

static int	_red_outputs(t_args *temp, int *i)
{
	int		fd;

	fd = -1;
	while (temp->output_files[++*i])
	{
		fd = -1;
		if (ft_strcmp(temp->output_redirs[*i], ">") == 0)
		{
			fd = open(temp->output_files[*i],
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
			temp->output_type = 0;
		}
		else if (ft_strcmp(temp->output_redirs[*i], ">>") == 0)
		{
			fd = open(temp->output_files[*i],
					O_WRONLY | O_APPEND | O_CREAT, 0644);
			temp->output_type = 1;
		}
		if (fd == -1)
			return (EXIT_FAILURE);
		close(fd);
	}
	return (EXIT_SUCCESS);
}

int	ft_redirections(t_pipex *pipex, t_struct *main)
{
	t_args	*temp;
	int		i;

	temp = main->args_list;
	while (temp)
	{
		i = -1;
		if (temp->input_files)
			if (_red_inputs(pipex, temp) == 1)
				return (EXIT_FAILURE);
		if (temp->output_files)
		{
			if (_red_outputs(temp, &i) == 1)
				return (EXIT_FAILURE);
			if (temp->output)
				(free(temp->output), temp->output = NULL);
			temp->output = ft_strdup(temp->output_files[i - 1]);
			if (!temp->output)
				return (EXIT_FAILURE);
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
