/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:06:41 by kcouchma          #+#    #+#             */
/*   Updated: 2024/01/24 16:34:19 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_last_cmd(t_pipex *pipex)
{
	int	out_fd;

	close(pipex->pipe_fd[1]);
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	close(pipex->pipe_fd[0]);
	out_fd = open(pipex->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (out_fd == -1)
	{
		perror("cannot open output file");
		ft_freetable(pipex->child_args);
		ft_freetable(pipex->paths);
		exit(EXIT_FAILURE);
	}
	dup2(out_fd, STDOUT_FILENO);
}

void	ft_first_cmd(t_pipex *pipex)
{
	int	in_fd;

	close(pipex->pipe_fd[0]);
	dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	close(pipex->pipe_fd[1]);
	in_fd = open(pipex->infile, O_RDONLY);
	if (in_fd == -1)
	{
		perror("cannot open input file");
		ft_freetable(pipex->child_args);
		ft_freetable(pipex->paths);
		exit(EXIT_FAILURE);
	}
	dup2(in_fd, STDIN_FILENO);
}

void	ft_forkchild(t_pipex *pipex, int i)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
	{
		perror("fork failed");
		ft_freetable(pipex->paths);
		exit(EXIT_FAILURE);
	}
	if (pipex->pid == 0)
	{
		pipex->child_args = ft_split(pipex->args[pipex->commands + 1 - i], ' ');
		if (!pipex->child_args)
		{
			write(STDERR_FILENO, "pipex: cmd parse failure", 24);
			ft_freetable(pipex->paths);
			exit(EXIT_FAILURE);
		}
		else if (!pipex->child_args[0])
			ft_command_fail(pipex);
		if (i == 0)
			ft_last_cmd(pipex);
		else if (i == 1)
			ft_first_cmd(pipex);
		ft_execve(pipex);
		ft_command_fail(pipex);
	}
}

void	ft_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipe(pipex->pipe_fd) == -1)
	{
		perror("pipe failed");
		ft_freetable(pipex->paths);
		exit(EXIT_FAILURE);
	}
	while (i < pipex->commands)
	{
		ft_forkchild(pipex, i);
		if (i == 0)
			pipex->pid_last = pipex->pid;
		if (pipex->pid != 0)
			close(pipex->pipe_fd[0]);
		i++;
	}
	if (pipex->pid != 0)
	{
		close(pipex->pipe_fd[1]);
		waitpid(pipex->pid, NULL, 0);
		waitpid(pipex->pid_last, &pipex->exit_code, 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.commands = argc - 3;
	pipex.envp = envp;
	pipex.args = argv;
	pipex.infile = argv[1];
	pipex.outfile = argv[argc - 1];
	pipex.child_args = NULL;
	pipex.exit_code = 0;
	pipex.paths = ft_extract_envp(envp);
	if (argc == 5)
		ft_pipex(&pipex);
	else
		ft_printf("pipex input error: ./pipex infile cmd1 cmd2 outfile\n");
	ft_freetable(pipex.paths);
	if (pipex.exit_code == 256)
		pipex.exit_code = 127;
	return (pipex.exit_code);
}
