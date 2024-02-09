/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:33:22 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/05 13:58:12 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

// chdir apparently handles relative and absolute paths and ".."

int ft_cd(int argc, char **argv, t_pipex *pipex)
{
	(void)pipex;
	if (argc > 2)
	{
		printf("finishell: cd: too many arguments");
		return (EXIT_FAILURE);
	}
	if (chdir(argv[1]) == -1)
	{
		perror("finishell: cd");
		return (EXIT_FAILURE);
	}
	//UPDATE $OLDPWD and $PWD in pipex->envp with export
	return (EXIT_SUCCESS);
}
