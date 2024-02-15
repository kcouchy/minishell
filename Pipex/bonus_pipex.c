/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:06:41 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/15 17:02:09 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"
#include "pipex.h"

void	ft_bonus_pipex(t_pipex *pipex, t_struct *main)
{
	int	i;

	i = 0;
	if (pipex->commands == 1)
	{
		// pipex->child_args = ft_split
		// 	(pipex->args[pipex->commands + 1 + pipex->heredoc - i], ' ');
		// if (!pipex->child_args)
		// 	ft_parse_fail(pipex);

		if (!main->args_list->command_name) //equivalent of command is missing - change this to just exiting without error
		{
			printf("here\n");
			ft_command_fail(pipex);
		}
		ft_single_cmd(pipex);
		ft_execve(pipex, main->args_list, main->common);
		ft_command_fail(pipex);
	}
	else
	{
		while (i < pipex->commands)
		{
			if (i < (pipex->commands - 1))
			{
				if (pipe(pipex->pipe_fd) == -1)
					ft_pipe_fail(pipex);
			}
			ft_bonus_forkchild(pipex, i, main);
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

void	ft_heredoc(t_pipex *pipex, t_args *args_list)
{
	char	*buffer;

	buffer = NULL;
	pipex->heredoc = 1;
	pipex->infile_fd = open("/tmp/temp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (pipex->infile_fd == -1)
	{
		write(STDERR_FILENO, "pipex: open failed: heredoc\n", 28);
		ft_open_fail(pipex);
	}
	while (1)
	{
		write(STDERR_FILENO, "> ", 2);
		buffer = get_next_line(STDIN_FILENO);
		if (!buffer)
			ft_byedoc(pipex);
		if (ft_strncmp(buffer, "\n", 1) != 0)
			if (ft_strncmp(buffer, args_list->input_files[0],
					(ft_strlen(buffer) - 1)) == 0)
				break ;
		write(pipex->infile_fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
	close(pipex->infile_fd);
}

void	ft_pipex_init(t_pipex *pipex, t_struct *main)
{
	// pipex->commands = num_args;
	// pipex->envp = envp;
	// pipex->args = argv;
	// pipex->infile = argv[1];
	pipex->infile_fd = -1;
	// pipex->outfile = argv[argc - 1];
	// pipex->child_args = NULL;
	// pipex->temp_fd_out = -1;
	pipex->heredoc = 0;
	// pipex->exit_code = 0;
	pipex->paths = ft_extract_paths(main->common->envp);
	// pipex->pwd_origin = getcwd(NULL, 0);
}

int		executing(t_struct *main)
{
	t_pipex	pipex;

	// ft_pipex_init(&pipex, argc, argv, envp, num_args);
	ft_pipex_init(&pipex, main);
	if (main->args_list->input_redirs)
		if (ft_strncmp(main->args_list->input_redirs[0], "<<", 2) == 0)
			ft_heredoc(&pipex, main->args_list);
	if (main->common->nb_commands < 1)
	{
		if (pipex.heredoc == 1)
			unlink("temp");
		return (0);
	}
	ft_bonus_pipex(&pipex, main);
	if (pipex.heredoc == 1 && pipex.infile_fd != -1)
	{
		close(pipex.infile_fd);
		unlink("temp");
	}
	ft_freetable(pipex.paths);
	free(pipex.pwd_origin);
	// printf("---------%d--------\n", pipex.exit_code);
	return (pipex.exit_code);
}
