/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:51:04 by lribette          #+#    #+#             */
/*   Updated: 2024/03/05 09:27:31 by lribette         ###   ########.fr       */
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
	free_table(pipex->paths);
	ft_structclear(&main->args_list);
	free_table(main->common.f_envp);
	free(main->common.pwd);
	rl_clear_history();
	if (errno == MALLOC_ERROR)
		exit(errno);
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
		if (errno == MALLOC_ERROR)
			return (NULL);
		f_envp[i] = ft_strjoin("?=", new_exit_str);
		if (errno == MALLOC_ERROR)
			return (free_table(f_envp), NULL);
		free(new_exit_str);
	}
	return (f_envp);
}

void	ft_write_join(char *error_type, char *cmd, char *arg, char *str)
{
	char	*join;

	join = ft_strjoinf(error_type, cmd, 0);
	if (join)
		join = ft_strjoinf(join, arg, 1);
	if (join)
		join = ft_strjoinf(join, str, 1);
	if (join)
		join = ft_strjoinf(join, "\n", 1);
	if (join)
		join = ft_strjoinf(join, RESET, 1);
	if (join)
		write(STDERR_FILENO, join, ft_strlen(join));
	if (join)
		free(join);
}
