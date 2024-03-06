/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:46:56 by kcouchma          #+#    #+#             */
/*   Updated: 2024/03/06 09:29:27 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Pipex/pipex.h"

int	ft_env(t_struct *main)
{
	int		i;
	size_t	j;
	char	**f_envp;

	i = 0;
	j = 0;
	f_envp = main->common.f_envp;
	if (!f_envp)
		return (EXIT_SUCCESS);
	while (f_envp[i])
	{
		j = ft_find_eq(f_envp[i]);
		if (ft_strncmp(f_envp[i], "?=", 2) != 0 && j != ft_strlen(f_envp[i]))
		{
			write(STDOUT_FILENO, f_envp[i], ft_strlen(f_envp[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
