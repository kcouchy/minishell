/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:59:31 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/22 18:51:30 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	_hd_read(t_pipex *pipex, t_args **temp, char *temp_i, int temp_fd, int i)
{
	char	*line;

	line = NULL;
	while (1)
	{
		write(STDERR_FILENO, "> ", 2);
		line = gnl(STDIN_FILENO);
		if (g_signal == 2)
		{
			close(temp_fd);
			temp_fd = open(temp_i, O_RDWR | O_TRUNC | O_CREAT, 0644);
			return (EXIT_SUCCESS); //does ctrl C exit leave it as a success?
		}
		if (!line)
			return (ft_byedoc(pipex, *temp, EXIT_SUCCESS)); //should be exit failure?
		else if (ft_strncmp(line, "\n", 1) != 0)
			if (ft_strncmp(line, (*temp)->input_files[i],
					(ft_strlen(line) - 1)) == 0)
				return (EXIT_SUCCESS);
		write(temp_fd, line, ft_strlen(line));
		if (!(*temp)->input_files[i][0] && ft_strncmp(line, "\n", 1) == 0) // should handle limiter of "", to end the heredoc
			return (EXIT_SUCCESS);
		free(line);
	}
	return (free(line), EXIT_SUCCESS);
}

int	ft_heredoc(t_pipex *pipex, t_args **temp, int i)
{
	char	*char_i;
	char	*temp_i;
	int		temp_fd;

	char_i = ft_itoa(i);
	if (!char_i)
		return (EXIT_FAILURE);
	temp_i = ft_strjoin("./Pipex/temp_", char_i);
	if (!temp_i)
		return (EXIT_FAILURE);
	if ((*temp)->input)
		(free((*temp)->input), (*temp)->input = NULL);
	(*temp)->input = temp_i;
	temp_fd = open(temp_i, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (temp_fd == -1) //can trigger this open fail with permissions for leak test
		return (EXIT_FAILURE);
	if (_hd_read(pipex, temp, temp_i, temp_fd, i) == 1)
		return (EXIT_FAILURE);
	g_signal = 0;
	free(char_i);
	close(temp_fd);
	signal(SIGINT, &sigint_handler);
	return (EXIT_SUCCESS);
}

static int	_inputs(t_pipex *pipex, t_args *temp)
{
	int		fd;
	int		i;

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
			if (ft_heredoc(pipex, &temp, i) == 1)
				return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	_outputs(t_args *temp, int *i)
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
	i = -1;
	while (temp)
	{
		if (temp->input_files)
			if (_inputs(pipex, temp) == 1)
				return (EXIT_FAILURE);
		if (temp->output_files)
		{
			if (_outputs(temp, &i) == 1)
				return (EXIT_FAILURE);
			if (temp->output)
				(free(temp->output), temp->output = NULL);
			temp->output = ft_strdup(temp->output_files[i - 1]);
			if (!temp->output)
				return (EXIT_FAILURE);
		}
		printf("temp->input %s\n", temp->input);//REMOVE
		printf("temp->output %s\n", temp->output);//REMOVE
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
