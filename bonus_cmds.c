/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:28:50 by kcouchma          #+#    #+#             */
/*   Updated: 2024/01/26 12:26:45 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_bonus_last_cmd(t_pipex *pipex)
{
	close(pipex->pipe_fd[1]);
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	close(pipex->pipe_fd[0]);
	if (pipex->heredoc == 1)
		pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_APPEND
				| O_CREAT, 0644);
	else
		pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_TRUNC
				| O_CREAT, 0644);
	if (pipex->outfile_fd == -1)
	{
		perror("cannot open output file");
		ft_freetable(pipex->child_args);
		ft_freetable(pipex->paths);
		exit(EXIT_FAILURE);
	}
	dup2(pipex->outfile_fd, STDOUT_FILENO);
}

void	ft_bonus_first_cmd(t_pipex *pipex)
{
	close(pipex->pipe_fd[0]);
	dup2(pipex->temp_fd_out, STDOUT_FILENO);
	close(pipex->temp_fd_out);
	if (pipex->heredoc == 1)
		pipex->infile_fd = open("/tmp/temp", O_RDONLY);
	else
		pipex->infile_fd = open(pipex->infile, O_RDONLY);
	if (pipex->infile_fd == -1)
	{
		perror("cannot open input file");
		ft_freetable(pipex->child_args);
		ft_freetable(pipex->paths);
		exit(EXIT_FAILURE);
	}
	dup2(pipex->infile_fd, STDIN_FILENO);
}

void	ft_bonus_mid_cmd(t_pipex *pipex)
{
	close(pipex->pipe_fd[1]);
	dup2(pipex->temp_fd_out, STDOUT_FILENO);
	close(pipex->temp_fd_out);
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	close(pipex->pipe_fd[0]);
}

void	ft_bonus_forkchild(t_pipex *pipex, int i)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
		(perror("fork failed"), ft_freetable(pipex->paths), exit(EXIT_FAILURE));
	if (pipex->pid == 0)
	{
		pipex->child_args = ft_split
			(pipex->args[pipex->commands + 1 + pipex->heredoc - i], ' ');
		if (!pipex->child_args)
			ft_parse_fail(pipex);
		else if (!pipex->child_args[0])
			ft_command_fail(pipex);
		if (i == 0)
			ft_bonus_last_cmd(pipex);
		else if (i == pipex->commands - 1)
			ft_bonus_first_cmd(pipex);
		else if (i > 0 && i < (pipex->commands - 1))
			ft_bonus_mid_cmd(pipex);
		ft_execve(pipex);
		ft_command_fail(pipex);
	}
	if (pipex->pid != 0)
		if (pipex->temp_fd_out != -1)
			close(pipex->temp_fd_out);
	if (pipex->pid != 0)
		pipex->temp_fd_out = pipex->pipe_fd[1];
}

void	ft_wait_parent(t_pipex *pipex)
{
	int	i;

	i = 1;
	waitpid(pipex->pid_last, &pipex->exit_code, 0);
	if (pipex->exit_code == 256)
		pipex->exit_code = 127;
	while (i < pipex->commands)
	{
		wait(NULL);
		i++;
	}
}
