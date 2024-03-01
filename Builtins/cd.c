/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:33:22 by kcouchma          #+#    #+#             */
/*   Updated: 2024/03/01 11:56:14 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./../Pipex/pipex.h"

int ft_cd(t_args *arg, t_struct *main)
{
	// char	*OLD_PWD;
	char	*NEW_PWD;

	// OLD_PWD = getcwd(NULL, 0);
	// OLD_PWD = ft_strjoinf("OLDPWD=", OLD_PWD, 2);
	// if (!OLD_PWD)
	// 	return (EXIT_FAILURE);
	if (!arg->args)
		arg->args = ex_fenvp("HOME=", main);
	if (chdir(arg->args) == -1)
	{
		write(STDERR_FILENO, "finishell: cd: No such file or directory\n", 41);
		// free (OLD_PWD);
		return (EXIT_FAILURE);
	}
	NEW_PWD = getcwd(NULL, 0);
	NEW_PWD = ft_strjoinf("PWD=", NEW_PWD, 2);
	if (!NEW_PWD)
		return (EXIT_FAILURE);
	// ft_mod_fevnp(OLD_PWD, main->common.f_envp);
	ft_mod_fevnp(NEW_PWD, &main->common.f_envp);
	// free(OLD_PWD);
	free(NEW_PWD);
	return (EXIT_SUCCESS);
}
