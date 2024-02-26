/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:46:56 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/26 18:32:00 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./../Pipex/pipex.h"

//loop through pipex->envp and write to STDOUT_FD
//newline?

static int	_find_null(char *f_envp)
{
	int	i;

	i = 0;
	while (f_envp[i] && f_envp[i] != '=')
		i++;
	if (f_envp)
		return (1);
	return (0);
}

int ft_env(t_struct *main)
{
	int		i;
	char	**f_envp;

	i = 0;
	f_envp = main->common.f_envp;
	// if (ft_tablen(main->args_list->command_table) > 1)
	// {
	// 	printf("finishell: env: too many arguments");
	// 	return (EXIT_FAILURE);
	// }
	// if (!f_envp)
	// {
	// 	printf("finishell: env: env is NULL");
	// 	return (EXIT_FAILURE);
	// }
	while (f_envp[i])
	{
		if(f_envp[i][0] != '_' && f_envp[i][0] != '?' && _find_null(f_envp[i]))
			write(STDOUT_FILENO, f_envp[i], ft_strlen(f_envp[i]));
		i++;
	}
	return (EXIT_SUCCESS);
}