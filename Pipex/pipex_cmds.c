/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:28:50 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/23 15:53:32 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// 0 = first command position = no redirection if there is no redirection in the command structure
// 1 = last/mid command position = redirection to/from pipe if there is no redirection in the command structure

void	ft_input(t_pipex *pipex, t_args *child_args, t_struct *main, int ired)
{
	int	in_fd;

	in_fd = -1;
	if (pipex->pipe_fd[ired] != -1)
		close(pipex->pipe_fd[ired]);
	if (!child_args->input && ired == 0)
		return ;
	if (child_args->input)
		in_fd = open(child_args->input, O_RDONLY);
	else
		in_fd = pipex->pipe_fd[0];
	if (in_fd == -1)
	{
		write(STDERR_FILENO, "finishell: open failed: last_cmd\n", 33);
		ft_pipex_error(pipex, main, EXIT_FAILURE);
	}
	if (dup2(in_fd, STDIN_FILENO) == -1)
	{
		write(STDERR_FILENO, "finishell: dup2 failed: last_cmd\n", 33);
		ft_pipex_error(pipex, main, EXIT_FAILURE);
	}
	if (ired == 1)
		close(in_fd);
}

// 0 = last command position = no redirection if there is no redirection in the command structure
// 1 = first/mid command position = redirection to/from pipe if there is no redirection in the command structure

void	ft_output(t_pipex *pipex, t_args *child_args, t_struct *main, int ored)
{
	int	out_fd;

	out_fd = -1;
	if (!child_args->output && ored == 0)
		return ;
	if (child_args->output)
	{
		if (child_args->output_type == 1)
			out_fd = open(child_args->output, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (child_args->output_type == 0)
			out_fd = open(child_args->output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	else
		out_fd = pipex->temp_fd_out;
	if (out_fd == -1)
	{
		write(STDERR_FILENO, "finishell: open failed: output\n", 31);
		ft_pipex_error(pipex, main, EXIT_FAILURE);
	}
	if (dup2(out_fd, STDOUT_FILENO) == -1)
	{
		write(STDERR_FILENO, "finishell: dup2 failed: output\n", 31);
		ft_pipex_error(pipex, main, EXIT_FAILURE);
	}
	if (ored == 1)
		close(out_fd);
}

void	ft_cmd(t_pipex *pipex, t_args *child_args, t_struct *main, int red)
{
	if (red >= 10)
	{
		ft_input(pipex, child_args, main, 1);
		ft_output(pipex, child_args, main, red % 10);
	}
	else
	{
		ft_input(pipex, child_args, main, 0);
		ft_output(pipex, child_args, main, red);
	}
}

void	ft_forkchild(t_pipex *pipex, int i, t_args *child_args, t_struct *main)
{
	g_signal = 1;
	pipex->pid = fork();
	if (pipex->pid == -1)
		ft_pipex_error(pipex, main, EXIT_FAILURE);
	if (pipex->pid == 0)
	{
		if (!child_args->command_name)
			ft_pipex_error(pipex, main, EXIT_SUCCESS);
		if (main->common.nb_commands == 1 && i == 0)
			ft_cmd(pipex, child_args, main, 00);
		else if (main->common.nb_commands > 1 && i == 0)
			ft_cmd(pipex, child_args, main, 10);
		else if (i == main->common.nb_commands - 1)
			ft_cmd(pipex, child_args, main, 01);
		else if (i > 0 && i < (main->common.nb_commands - 1))
			ft_cmd(pipex, child_args, main, 11);
		if (!child_args->command_table[0])
			ft_command_fail(pipex, child_args, main);
		ft_execve(pipex, child_args, main);
		ft_command_fail(pipex, child_args, main);
	}
	if (pipex->pid != 0)
		if (pipex->temp_fd_out != -1)
			close(pipex->temp_fd_out);
	if (pipex->pid != 0)
		pipex->temp_fd_out = pipex->pipe_fd[1];
}

void	ft_wait_parent(t_pipex *pipex, int nb_commands)
{
	int	i;

	i = 1;
	waitpid(pipex->pid_last, &pipex->exit_code, 0);
	pipex->exit_code = WEXITSTATUS(pipex->exit_code);
	while (i < nb_commands)
	{
		wait(NULL);
		i++;
	}
}
