/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:33:22 by kcouchma          #+#    #+#             */
/*   Updated: 2024/03/05 23:00:40 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Pipex/pipex.h"

static int	_cd_error(t_args *arg)
{
	if (ft_tablen(arg->command_table) > 2)
		ft_write_join(RED, " cd: ", "", "too many arguments");
	else
	{
		write(STDERR_FILENO, RED" cd: ", 37);
		write(STDERR_FILENO, arg->args, ft_strlen(arg->args));
		write(STDERR_FILENO, ": ", 2);
		perror("");
		write(STDERR_FILENO, RESET, ft_strlen(RESET));
	}
	return (EXIT_FAILURE);
}

static void	_ft_home(t_args *arg, t_struct *main)
{
	char	*temp;

	if (!arg->args)
		arg->args = ex_fenvp("HOME=", main);
	else if (arg->args[0] == '~')
	{
		temp = ft_strjoinf(ex_fenvp("HOME=", main), arg->args + 1, 1);
		free(arg->args);
		arg->args = temp;
	}
}

int	ft_cd(t_args *arg, t_struct *main)
{
	char	*new_pwd;

	_ft_home(arg, main);
	if (errno == MALLOC_ERROR)
		return (errno);
	if (arg->args[0] == '\0')
		return (EXIT_SUCCESS);
	if (chdir(arg->args) == -1)
		return (_cd_error(arg));
	new_pwd = getcwd(NULL, 0);
	new_pwd = ft_strjoinf("PWD=", new_pwd, 2);
	if (!new_pwd)
		return (errno);
	ft_mod_fevnp(new_pwd, &main->common.f_envp);
	if (errno == MALLOC_ERROR)
		return (errno);
	free(new_pwd);
	return (EXIT_SUCCESS);
}
