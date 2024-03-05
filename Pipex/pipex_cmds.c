/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:28:50 by kcouchma          #+#    #+#             */
/*   Updated: 2024/03/05 14:35:39 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	_open_fail(t_pipex *pipex, t_struct *main)
{
	ft_write_join(SHIT, " open failed:", "", " input/output");
	ft_pipex_error(pipex, main, EXIT_FAILURE);
}

void	ft_input(t_pipex *pipex, t_args *arg, t_struct *main, int ired)
{
	int	in_fd;

	in_fd = -1;
	if (pipex->pipe_fd[ired] != -1)
		close(pipex->pipe_fd[ired]);
	if (!arg->input && ired == 0)
		return ;
	if (arg->input)
		in_fd = open(arg->input, O_RDONLY);
	else
		in_fd = pipex->pipe_fd[0];
	if (in_fd == -1)
		_open_fail(pipex, main);
	if (dup2(in_fd, STDIN_FILENO) == -1)
	{
		ft_write_join(SHIT, " dup2 failed:", "", " input");
		ft_pipex_error(pipex, main, EXIT_FAILURE);
	}
	close(pipex->pipe_fd[0]);
	if (arg->input)
		close(in_fd);
}

void	ft_output(t_pipex *pipex, t_args *arg, t_struct *main, int ored)
{
	int	out_fd;

	out_fd = -1;
	if (!arg->output && ored == 0)
		return ;
	if (arg->output)
	{
		if (arg->output_type == 1)
			out_fd = open(arg->output, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (arg->output_type == 0)
			out_fd = open(arg->output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (pipex->temp_fd_out != -1)
			close (pipex->temp_fd_out);
	}
	else
		out_fd = pipex->temp_fd_out;
	if (out_fd == -1)
		_open_fail(pipex, main);
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		ft_write_join(SHIT, " dup2 failed:", "", " output");
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		ft_pipex_error(pipex, main, EXIT_FAILURE);
	if (out_fd != -1)
		close(out_fd);
}

void	ft_cmd(t_pipex *pipex, t_args *arg, t_struct *main, int i)
{
	int	red;

	red = -1;
	if (main->common.nb_commands == 1 && i == 0)
		red = 00;
	else if (main->common.nb_commands > 1 && i == 0)
		red = 10;
	else if (i == main->common.nb_commands - 1)
		red = 01;
	else if (i > 0 && i < (main->common.nb_commands - 1))
		red = 11;
	else
		return ;
	if (red >= 10)
	{
		ft_input(pipex, arg, main, 1);
		ft_output(pipex, arg, main, red % 10);
	}
	else
	{
		ft_input(pipex, arg, main, 0);
		ft_output(pipex, arg, main, red);
	}
}

void	ft_forkchild(t_pipex *pipex, int i, t_args *arg, t_struct *main)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
		ft_pipex_error(pipex, main, EXIT_FAILURE);
	if (pipex->pid == 0)
	{
		if (!arg->command_name)
		{
			close(pipex->pipe_fd[0]);
			close(pipex->pipe_fd[1]);
			ft_pipex_error(pipex, main, EXIT_SUCCESS);
		}
		ft_cmd(pipex, arg, main, i);
		if (!arg->command_table[0])
			ft_command_fail(pipex, arg, main);
		ft_execve(pipex, arg, main);
		if (arg->is_builtin)
			ft_builtin_fail(pipex, arg, main);
		else
			ft_command_fail(pipex, arg, main);
	}
	if (pipex->pid != 0)
		if (pipex->temp_fd_out != -1)
			close(pipex->temp_fd_out);
	if (pipex->pid != 0)
		pipex->temp_fd_out = pipex->pipe_fd[1];
}
