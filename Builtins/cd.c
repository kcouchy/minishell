/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:33:22 by kcouchma          #+#    #+#             */
/*   Updated: 2024/03/03 10:10:12 by lribette         ###   ########.fr       */
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

int	ft_cd(t_args *arg, t_struct *main)
{
	char	*NEW_PWD;

	if (!arg->args)
		arg->args = ex_fenvp("HOME=", main);
	if (chdir(arg->args) == -1)
		return (_cd_error(arg));
	NEW_PWD = getcwd(NULL, 0);
	NEW_PWD = ft_strjoinf("PWD=", NEW_PWD, 2);
	if (!NEW_PWD)
		return (errno);
	ft_mod_fevnp(NEW_PWD, &main->common.f_envp);
	if (errno == MALLOC_ERROR)
		return (errno);
	free(NEW_PWD);
	return (EXIT_SUCCESS);
}
