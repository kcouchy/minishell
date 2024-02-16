/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:06:41 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/16 18:35:10 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"
#include "pipex.h"

void	ft_bonus_pipex(t_pipex *pipex, t_struct *main)
{
	int		i;
	t_args	*child_args;

	child_args = main->args_list;
	i = 0;
	if (main->common.nb_commands == 1)
	{
		if (!child_args->command_name) //equivalent of command is missing - as with bash, exits without error
			return ;
		ft_single_cmd(pipex, child_args);
		ft_execve(pipex, child_args, main->common.envp);
		ft_command_fail(pipex, child_args, main);
	}
	else
	{
		while (child_args)
		{
			if (i < (main->common.nb_commands - 1))
			{
				if (pipe(pipex->pipe_fd) == -1)
					ft_pipe_fail(pipex);
			}
			ft_bonus_forkchild(pipex, i, child_args, main);
			if (i == 0)
				pipex->pid_last = pipex->pid;
			if (i < (main->common.nb_commands - 1))
				close(pipex->pipe_fd[0]);
			i++;
			child_args = child_args->next;
		}
		if (pipex->pid != 0)
			ft_wait_parent(pipex, main->common.nb_commands);
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
		write(STDERR_FILENO, "finishell: open failed: heredoc\n", 32);
		ft_open_fail(pipex);
	}
	while (1)
	{
		write(STDERR_FILENO, "> ", 2);
		buffer = get_next_line(STDIN_FILENO);
		if (!buffer)
			ft_byedoc(pipex, args_list);
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
	pipex->infile_fd = -1;
	pipex->temp_fd_out = -1;
	pipex->heredoc = 0;
	pipex->exit_code = 0;
	pipex->paths = ft_extract_paths(main->common.envp);
}

int		executing(t_struct *main)
{
	t_pipex	pipex;

	ft_pipex_init(&pipex, main);
	if (main->args_list->input_redirs) //will need to loop this to do as many heredocs as there are for each command (nodes on args_list)
		if (ft_strcmp(main->args_list->input_redirs[0], "<<") == 0)
			ft_heredoc(&pipex, main->args_list);
			//will have to run the heredoc on loop through the structures in args_list, amd through input_args
	if (main->common.nb_commands < 1)
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
	// printf("---------%d--------\n", pipex.exit_code);
	return (pipex.exit_code);
}
