/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:28:50 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/22 10:14:14 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_inputs(t_pipex *pipex, t_args *child_args, t_struct *main)
{
	int	in_fd;

	in_fd = -1;
	if (!child_args->input)
		return ;
	in_fd = open(child_args->input, O_RDONLY);
	if (in_fd == -1)
	{
		write(STDERR_FILENO, "finishell: open failed: input\n", 30);
		ft_pipex_error(pipex, main, EXIT_FAILURE);
	}
	if (dup2(in_fd, STDIN_FILENO) == -1)
	{
		write(STDERR_FILENO, "finishell: dup2 failed: input\n", 30);
		ft_pipex_error(pipex, main, EXIT_FAILURE);
	}
}

void	ft_outputs(t_pipex *pipex, t_args *child_args, t_struct *main)
{
	int	out_fd;

	out_fd = -1;
	if (!child_args->output)
		return ;
	if (child_args->output_type == 1)
		out_fd = open(child_args->output, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (child_args->output_type == 0)
		out_fd = open(child_args->output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
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
}

void	ft_last_cmd(t_pipex *pipex, t_args *child_args, t_struct *main) //can modify ft_inputs to handle most of this
{
	int	in_fd;

	in_fd = -1;
	close(pipex->pipe_fd[1]);
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
	// if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
	// {
	// 	write(STDERR_FILENO, "pipex: dup2 failed: last_cmd\n", 29);
	// 	ft_dup2_fail(pipex);
	// }
	close(in_fd);
	ft_outputs(pipex, child_args, main);
}

void	ft_first_cmd(t_pipex *pipex, t_args *child_args, t_struct *main) //can modify ft_outputs to handle most of this
{
	int	out_fd;

	out_fd = -1;
	close(pipex->pipe_fd[0]);
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
		write(STDERR_FILENO, "finishell: open failed: first_cmd\n", 34);
		ft_pipex_error(pipex, main, EXIT_FAILURE);
	}
	if (dup2(out_fd, STDOUT_FILENO) == -1)
	{
		write(STDERR_FILENO, "finishell: dup2 failed: first_cmd\n", 34);
		ft_pipex_error(pipex, main, EXIT_FAILURE);
	}
	// if (dup2(pipex->temp_fd_out, STDOUT_FILENO) == -1)
	// {
	// 	write(STDERR_FILENO, "pipex: dup2 failed: first_cmd\n", 30);
	// 	ft_dup2_fail(pipex);
	// }
	close(out_fd);
	ft_inputs(pipex, child_args, main);
}

void	ft_mid_cmd(t_pipex *pipex, t_args *child_args, t_struct *main)
{
	int	out_fd;
	int	in_fd;

	out_fd = -1;
	in_fd = -1;
	close(pipex->pipe_fd[1]);
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
		write(STDERR_FILENO, "finishell: open failed: mid_cmd\n", 32);
		ft_pipex_error(pipex, main, EXIT_FAILURE);
	}
	if (dup2(out_fd, STDOUT_FILENO) == -1)
	{
		write(STDERR_FILENO, "finishell: dup2 failed: mid_cmd\n", 32);
		ft_pipex_error(pipex, main, EXIT_FAILURE);
	}
	if (child_args->input)
		in_fd = open(child_args->input, O_RDONLY);
	else
		in_fd = pipex->pipe_fd[0];
	if (in_fd == -1)
	{
		write(STDERR_FILENO, "finishell: open failed: mid_cmd\n", 32);
		ft_pipex_error(pipex, main, EXIT_FAILURE);
	}
	if (dup2(in_fd, STDIN_FILENO) == -1)
	{
		write(STDERR_FILENO, "finishell: dup2 failed: mid_cmd\n", 32);
		ft_pipex_error(pipex, main, EXIT_FAILURE);
	}
	//if (outfile) then dup2 to outfile, else if :
	// if (dup2(pipex->temp_fd_out, STDOUT_FILENO) == -1)
	// {
	// 	write(STDERR_FILENO, "pipex: dup2 failed: mid_cmd\n", 28);
	// 	ft_dup2_fail(pipex);
	// }
	// close(pipex->temp_fd_out);


	//if (infile) then dup2 to infile, else if :
	// if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
	// {
	// 	write(STDERR_FILENO, "pipex: dup2 failed: mid_cmd\n", 28);
	// 	ft_dup2_fail(pipex);
	// }
	// close(pipex->pipe_fd[0]);
	close(out_fd);
	close(in_fd);
}

void	ft_forkchild(t_pipex *pipex, int i, t_args *child_args, t_struct *main)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
		ft_pipex_error(pipex, main, EXIT_FAILURE);
	if (pipex->pid == 0)
	{
		if (!child_args->command_name) //equivalent of command is missing - as with bash, exits without error
			ft_pipex_error(pipex, main, EXIT_SUCCESS);
		if (main->common.nb_commands == 1 && i == 0)
			ft_single_cmd(pipex, child_args, main);
		else if (main->common.nb_commands > 1 && i == 0)
			ft_last_cmd(pipex, child_args, main);
		else if (i == main->common.nb_commands - 1)
			ft_first_cmd(pipex, child_args, main);
		else if (i > 0 && i < (main->common.nb_commands - 1))
			ft_mid_cmd(pipex,child_args, main);
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
