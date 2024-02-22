/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:06:41 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/22 19:04:03 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"
#include "pipex.h"

void	ft_pipex(t_pipex *pipex, t_struct *main)
{
	int		i;
	t_args	*child_args;

	child_args = main->args_list;
	i = 0;
	while (child_args)
	{
		if (i < (main->common.nb_commands - 1))
		{
			if (pipe(pipex->pipe_fd) == -1)
			{
				write(STDERR_FILENO, "finishell: pipe failed\n", 23);
				ft_pipex_error(pipex, main, EXIT_FAILURE);
			}
		}
		ft_forkchild(pipex, i, child_args, main);
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

int	ft_pipex_init(t_pipex *pipex, t_struct *main)
{
	pipex->temp_fd_out = -1;
	pipex->pid = -1;
	pipex->exit_code = 0;
	pipex->paths = ft_extract_paths(main->common.envp);
	if (!pipex->paths)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		executing(t_struct *main)
{
	t_pipex	pipex;

	if (ft_pipex_init(&pipex, main) == EXIT_FAILURE)
	{
		write(STDERR_FILENO, "finishell: executing failure : init\n", 36);
		return (EXIT_FAILURE);
	}
	if (ft_redirections(&pipex, main) == EXIT_FAILURE)
	{
		write(STDERR_FILENO, "finishell: open failure : redirections\n", 39);
		return (ft_pipex_error(&pipex, main, EXIT_FAILURE));
	}
	if (main->common.nb_commands < 1)
		return (ft_pipex_error(&pipex, main, EXIT_SUCCESS));
	ft_pipex(&pipex, main);
	ft_pipex_error(&pipex, main, EXIT_SUCCESS);
	return (pipex.exit_code);
}
