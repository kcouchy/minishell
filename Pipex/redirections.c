/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:59:31 by kcouchma          #+#    #+#             */
/*   Updated: 2024/03/08 18:55:51 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	_red_inputs_open(t_args *temp, int i)
{
	int		fd;

	fd = open(temp->input_files[i], O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	close(fd);
	if (temp->input)
	{
		free(temp->input);
		temp->input = NULL;
	}
	temp->input = ft_strdup(temp->input_files[i]);
	if (!temp->input)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	_red_inputs(t_pipex *pipex, t_args *temp, int arg_num)
{
	int		i;
	int		hd_in;

	i = -1;
	while (temp->input_files[++i])
	{
		if (ft_strcmp(temp->input_redirs[i], "<") == 0)
		{
			if (_red_inputs_open(temp, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (ft_strcmp(temp->input_redirs[i], "<<") == 0)
		{
			hd_in = ft_heredoc(pipex, &temp, i, arg_num);
			if (hd_in != EXIT_SUCCESS)
				return (hd_in);
		}
	}
	return (EXIT_SUCCESS);
}

static int	_red_outputs(t_args *temp)
{
	int		fd;
	int		i;

	fd = -1;
	i = -1;
	while (temp->output_files[++i])
	{
		fd = -1;
		if (ft_strcmp(temp->output_redirs[i], ">") == 0)
		{
			fd = open(temp->output_files[i],
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
			temp->output_type = 0;
		}
		else if (ft_strcmp(temp->output_redirs[i], ">>") == 0)
		{
			fd = open(temp->output_files[i],
					O_WRONLY | O_APPEND | O_CREAT, 0644);
			temp->output_type = 1;
		}
		if (fd == -1)
			return (EXIT_FAILURE);
		close(fd);
	}
	return (EXIT_SUCCESS);
}

static int	_ft_redirs_recursive(t_pipex *pipex, t_struct *main,
								t_args *temp, int num)
{
	if (temp == NULL)
		return (EXIT_SUCCESS);
	if (_ft_redirs_recursive(pipex, main, temp->next, num + 1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (temp->input_files)
	{
		if (_red_inputs(pipex, temp, num) == 1)
			return (EXIT_FAILURE);
	}
	if (temp->output_files)
	{
		if (_red_outputs(temp) == 1)
			return (EXIT_FAILURE);
		if (temp->output)
			free(temp->output);
		if (temp->output)
			temp->output = NULL;
		temp->output = ft_strdup(temp->output_files[ft_tablen(
					temp->output_files) - 1]);
		if (!temp->output)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_redirections(t_pipex *pipex, t_struct *main)
{
	return (_ft_redirs_recursive(pipex, main, main->args_list, 0));
}
