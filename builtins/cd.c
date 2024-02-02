/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:33:22 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/02 12:07:34 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// cd .. take off everything after the last \)
// relative path - if arg does not start with \ then add to the end of getenv
// otherwise replace getenv with the path given

int ft_cd(char *command)
{
	char	*pwd;
	char	*temp;
	pwd = getcwd(NULL, 0);
	if (ft_strncmp(command, "..", 2) == 0)
	{
		temp = ft_strrchr(pwd, '/');
		*temp = '\0';
	}
	else if (command[0] == '/')
		pwd = ft_strjoin3("", "", command);
	else if (command[0] != '/')
		pwd = ft_strjoin3(pwd, "/", command);
	if (chdir(pwd) == -1)
	{
		perror("finishell: cd");
		free(pwd);
		exit(EXIT_FAILURE);
	}
	//UPDATE $OLDPWD and $PWD
	free(pwd);
	return (0);
}
