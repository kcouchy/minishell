/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:46:56 by kcouchma          #+#    #+#             */
/*   Updated: 2024/03/01 12:38:27 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Pipex/pipex.h"

static int	_arg_null(char *f_envp)
{
	int	i;

	i = 0;
	while (f_envp[i] && f_envp[i] != '=')
		i++;
	if (f_envp)
		return (0);
	return (1);
}

int	ft_env(t_struct *main)
{
	int		i;
	char	**f_envp;

	i = 0;
	f_envp = main->common.f_envp;
	while (f_envp[i])
	{
		if (ft_strncmp(f_envp[i], "?=", 2) != 0 && !_arg_null(f_envp[i]))
		{
			write(STDOUT_FILENO, f_envp[i], ft_strlen(f_envp[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
