/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:59:31 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/22 16:52:44 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
				return(EXIT_FAILURE);
		if (temp->output_files)
		{
			if (_outputs(temp, &i) == 1)
				return(EXIT_FAILURE);
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
	return (0);
}
