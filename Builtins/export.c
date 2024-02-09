/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:10:57 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/05 14:01:33 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

// if export only, print all of envp to the terminal except the variable "_"
// copy and sort envp, then in loop add declare -x add "" around the string(after = and at the end)

// if export (variable), then add "variable"+"="+"variable value" to env
// if export (variable=value), then add "variable=value" to env
// in both cases, overwrite variable if present, add if not

int ft_export(int argc, char **argv, t_pipex *pipex)
{
	int	i;

	i = 0;
	(void)argv;
	if (argc == 1)
	{
		while(pipex->envp[i])
		{
			if (pipex->envp[i][0] != '_')
				write(STDOUT_FILENO, pipex->envp[i], ft_strlen(pipex->envp[i]));
			i++;
		}
	}
	return (EXIT_SUCCESS);
}