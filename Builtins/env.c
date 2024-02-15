/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:46:56 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/15 12:15:00 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./../Pipex/pipex.h"

//loop through pipex->envp and write to STDOUT_FD
//newline?

int ft_env(int argc, char **argv, t_pipex *pipex)
{
	int	i;

	i = 0;
	(void)argv;
	if (argc > 1)
	{
		printf("finishell: env: too many arguments");
		return (EXIT_FAILURE);
	}
	while (pipex->envp[i])
	{
		write(STDOUT_FILENO, pipex->envp[i], ft_strlen(pipex->envp[i]));
		i++;
	}
	return (EXIT_SUCCESS);
}