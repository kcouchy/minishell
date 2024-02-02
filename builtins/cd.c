/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:33:22 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/02 17:44:01 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// chdir apparently handles relative and absolute paths and ".."

int cd(int argc, char **argv, t_pipex *pipex)
{
	if (argc > 2)
	{
		printf("finishell: cd: too many arguments");
		exit(EXIT_FAILURE);
	}
	if (chdir(argv[1]) == -1)
	{
		perror("finishell: cd");
		exit(EXIT_FAILURE);
	}
	//UPDATE $OLDPWD and $PWD in pipex->envp with export
	return (0);
}
