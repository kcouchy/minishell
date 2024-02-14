/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:33:22 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/14 14:11:32 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

//print from f_envp except for args that are ""

int ft_pwd(int argc, t_pipex *pipex)
{
	char	*pwd;

	(void) pipex;
	if (argc > 1)
	{
		printf("finishell: pwd: too many arguments");
		return (EXIT_FAILURE);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		printf("%s\n", pipex->pwd_origin);
	else
		printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
