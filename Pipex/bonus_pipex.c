/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:06:41 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/09 10:55:12 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_bonus_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->commands == 1)
	{
		pipex->child_args = ft_split
			(pipex->args[pipex->commands + 1 + pipex->heredoc - i], ' ');
		if (!pipex->child_args)
			ft_parse_fail(pipex);
		else if (!pipex->child_args[0])
			ft_command_fail(pipex);
		ft_single_cmd(pipex);
		ft_execve(pipex);
		ft_command_fail(pipex);
	}
	else
	{
		while (i < pipex->commands)
		{
			if (i < (pipex->commands - 1))
			{
				if (pipe(pipex->pipe_fd) == -1)
				{
					write(STDERR_FILENO, "pipex: pipe failed\n", 19);
					ft_freetable(pipex->paths);
					free(pipex->pwd_origin);
					exit(EXIT_FAILURE);
				}
			}
			ft_bonus_forkchild(pipex, i);
			if (i == 0)
				pipex->pid_last = pipex->pid;
			if (i < (pipex->commands - 1))
				close(pipex->pipe_fd[0]);
			i++;
		}
		if (pipex->pid != 0)
			ft_wait_parent(pipex);
	}
}

void	ft_heredoc(t_pipex *pipex)
{
	char	*buffer;

	buffer = NULL;
	pipex->heredoc = 1;
	pipex->infile_fd = open("/tmp/temp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (pipex->infile_fd == -1)
		ft_input_fail(pipex);
	while (1)
	{
		write(STDERR_FILENO, "> ", 2);
		buffer = get_next_line(STDIN_FILENO);
		if (!buffer)
			ft_byedoc(pipex);
		if (ft_strncmp(buffer, "\n", 1) != 0)
			if (ft_strncmp(buffer, pipex->args[2],
					(ft_strlen(buffer) - 1)) == 0)
				break ;
		write(pipex->infile_fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
	close(pipex->infile_fd);
}

void	ft_pipex_init(t_pipex *pipex, int argc, char **argv, char **envp, int num_args)
{
	pipex->commands = num_args;
	pipex->envp = envp;
	pipex->args = argv;
	pipex->infile = argv[1];
	pipex->infile_fd = -1;
	pipex->outfile = argv[argc - 1];
	pipex->child_args = NULL;
	pipex->temp_fd_out = -1;
	pipex->heredoc = 0;
	pipex->exit_code = 0;
	pipex->paths = ft_extract_envp(envp);
	pipex->pwd_origin = getcwd(NULL, 0);
}

int	executing(int argc, char **argv, char **envp, int num_args)
{
	t_pipex	pipex;

	ft_pipex_init(&pipex, argc, argv, envp, num_args);
	if (ft_strncmp(argv[1], "hd", 2) == 0)
		ft_heredoc(&pipex);
	if (num_args >= 1)
		ft_bonus_pipex(&pipex);
	else if (pipex.heredoc == 0)
	{
		ft_printf("minishell input error:\n");
		ft_printf("./minishell infile cmd1 ... cmdn outfile\n");
		ft_printf("./minishell hd LIMITER cmd1 ... cmdn outfile\n");
	}
	else if (pipex.heredoc == 1)
	{
		ft_printf("minishell input error:\n");
	}
	if (pipex.heredoc == 1 && pipex.infile_fd != -1)
	{
		close(pipex.infile_fd);
		unlink("temp");
	}
	ft_freetable(pipex.paths);
	free(pipex.pwd_origin);
	printf("---------%d--------\n", pipex.exit_code);
	return (pipex.exit_code);
}
