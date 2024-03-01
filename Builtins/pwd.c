/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:33:22 by kcouchma          #+#    #+#             */
/*   Updated: 2024/03/01 12:38:56 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Pipex/pipex.h"

//print from f_envp except for args that are ""

int	ft_pwd(t_args *arg, t_struct *main)
{
	char	*pwd;

	(void)arg;
	(void)main;
	pwd = getcwd(NULL, 0);
	// if (!pwd)
	// 	printf("%s\n", pwd_origin once it is initiated in minishell.c);
	// else
		printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
