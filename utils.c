/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:51:04 by lribette          #+#    #+#             */
/*   Updated: 2024/03/01 07:23:50 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./Pipex/pipex.h"

int	is_builtin(char *command)
{
	if (!command)
		return (0);
	if (!ft_strcmp(command, "echo"))
		return (1);
	if (!ft_strcmp(command, "cd"))
		return (1);
	if (!ft_strcmp(command, "pwd"))
		return (1);
	if (!ft_strcmp(command, "export"))
		return (1);
	if (!ft_strcmp(command, "unset"))
		return (1);
	if (!ft_strcmp(command, "env"))
		return (1);
	if (!ft_strcmp(command, "exit"))
		return (1);
	return (0);
}

void	ft_exit_error(t_pipex *pipex, t_struct *main, int exit_code)
{
	ft_freetable(pipex->paths);
	ft_structclear(&main->args_list);
	free_envp(main->common.f_envp);
	rl_clear_history();
	exit(exit_code);
}

char	**ch_exit_code(int exit_code, char **f_envp)
{
	int		i;
	char	*new_exit_str;

	i = 0;
	if (f_envp)
	{
		i = find_arg("?=", f_envp);
		if (i)
			free(f_envp[i]);
		new_exit_str = ft_itoa(exit_code);
		f_envp[i] = ft_strjoin("?=", new_exit_str);
		free(new_exit_str);
	}
	return (f_envp);
}
