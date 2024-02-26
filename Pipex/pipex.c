/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:06:41 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/26 14:23:00 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"
#include "pipex.h"

void	ft_pipex(t_pipex *pipex, t_struct *main)
{
	int		i;
	t_args	*arg;

	i = 0;
	arg = main->args_list;
	while (arg)
	{
		if (i < (main->common.nb_commands - 1) && (pipe(pipex->pipe_fd) == -1))
		{
			write(STDERR_FILENO, "finishell: pipe failed\n", 23);
			ft_pipex_error(pipex, main, EXIT_FAILURE);
		}
		g_signal = 1;
		ft_forkchild(pipex, i, arg, main);
		if (i == 0)
			pipex->pid_last = pipex->pid;
		if (i < (main->common.nb_commands - 1))
			close(pipex->pipe_fd[0]);
		i++;
		arg = arg->next;
	}
	if (pipex->pid != 0)
		ft_wait_parent(pipex, main->common.nb_commands);
}

int	ft_pipex_init(t_pipex *pipex, t_struct *main)
{
	pipex->temp_fd_out = -1;
	pipex->pid = -1;
	pipex->exit_code = 0;
	pipex->hd_temp_fd = -1;
	pipex->pipe_fd[0] = -1;
	pipex->pipe_fd[1] = -1;
	pipex->paths = ft_extract_paths(main->common.f_envp);
	if (!pipex->paths)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	executing(t_struct *main)
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
	g_signal = 0;
	ft_pipex_error(&pipex, main, EXIT_SUCCESS);
	return (pipex.exit_code);
}
