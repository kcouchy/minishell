/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:06:41 by kcouchma          #+#    #+#             */
/*   Updated: 2024/03/01 16:30:54 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"
#include "pipex.h"

void	sigint_handler_fork(int signal)
{
	write(1, "\n", 1);
	if (signal == SIGINT)
		g_signal = EXIT_SIGINT;
	if (signal == SIGQUIT)
		g_signal = EXIT_SIGQUIT;
}

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
		signal(SIGINT, &sigint_handler_fork);
		signal(SIGQUIT, &sigint_handler_fork);
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

	errno = 0;
	if (ft_pipex_init(&pipex, main) == EXIT_FAILURE)
		return (errno);
	if (ft_redirections(&pipex, main) == EXIT_FAILURE)
	{
		write(STDERR_FILENO, "finishell: open failure : redirections\n", 39);
		return (ft_pipex_error(&pipex, main, EXIT_FAILURE));
	}
	if (main->common.nb_commands < 1)
		return (ft_pipex_error(&pipex, main, EXIT_SUCCESS));
	if (main->common.nb_commands == 1 && main->args_list->is_builtin
		&& !(ft_strcmp(main->args_list->command_name, "echo") == 0)
		&& !(ft_strcmp(main->args_list->command_name, "env") == 0)
		&& !(ft_strcmp(main->args_list->command_name, "pwd") == 0)
		&& !((ft_strcmp(main->args_list->command_name, "export") == 0)
		&& !main->args_list->args))
			builtins_executing(&pipex, main->args_list, main);
	else
		ft_pipex(&pipex, main);
	signal(SIGINT, &sigint_handler);
	ft_pipex_error(&pipex, main, EXIT_SUCCESS);
	return (pipex.exit_code);
}
