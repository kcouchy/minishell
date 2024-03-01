/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:33:22 by kcouchma          #+#    #+#             */
/*   Updated: 2024/03/01 12:40:52 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Pipex/pipex.h"

static int	_cd_error(t_args *arg)
{
	if (ft_tablen(arg->command_table) > 2)
		ft_write_join(RED, " cd: ", "", "too many arguments");
	else
	{
		write(STDOUT_FILENO, RED" cd: ", 37);
		write(STDOUT_FILENO, arg->args, ft_strlen(arg->args));
		write(STDOUT_FILENO, ": ", 2);
		perror("");
		write(STDOUT_FILENO, RESET, ft_strlen(RESET));
	}
	return (EXIT_FAILURE);
}

int	ft_cd(t_args *arg, t_struct *main)
{
	// char	*OLD_PWD;
	char	*NEW_PWD;

	// OLD_PWD = getcwd(NULL, 0);
	// OLD_PWD = ft_strjoinf("OLDPWD=", OLD_PWD, 2);
	// if (!OLD_PWD)
	// 	return (EXIT_FAILURE);
	if (!arg->args)
		arg->args = ex_fenvp("OLDPWD=", main);
	if (!arg->args[0])
		return (EXIT_SUCCESS);
	if (chdir(arg->args) == -1)
		return (_cd_error(arg));
	NEW_PWD = getcwd(NULL, 0);
	NEW_PWD = ft_strjoinf("PWD=", NEW_PWD, 2);
	if (!NEW_PWD)
		return (EXIT_FAILURE);
	// ft_mod_fevnp(OLD_PWD, main->common.f_envp);
	ft_mod_fevnp(NEW_PWD, main->common.f_envp);
	// free(OLD_PWD);
	free(NEW_PWD);
	return (EXIT_SUCCESS);
}
