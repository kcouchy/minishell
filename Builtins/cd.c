/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:33:22 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/28 16:56:04 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./../Pipex/pipex.h"

// chdir apparently handles relative and absolute paths and ".."
static char	*_ft_strljoin(char *s1, char *s2, int len)
{
	int		i;
	int		j;
	char	*output;

	i = 0;
	j = 0;
	output = malloc(ft_strlen(s1) + len + 1);
	if (!output)
		return (NULL);
	while (s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	while (len > 0)
	{
		output[i] = s2[j];
		i++;
		j++;
		len--;
	}
	output[i] = '\0';
	free(s2);
	return (output);
}


int ft_cd(t_args *arg, t_struct *main)
{
	char	*OLD_PWD;
	char	*NEW_PWD;

	OLD_PWD = getcwd(NULL, 0);
	OLD_PWD = _ft_strljoin("OLDPWD=", OLD_PWD, ft_strlen(OLD_PWD));
	if (!OLD_PWD)
		return (EXIT_FAILURE);
	if (chdir(arg->command_table[1]) == -1)
	{
		printf("finishell: cd: chdir failure");
		free (OLD_PWD);
		return (EXIT_FAILURE);
	}
	NEW_PWD = getcwd(NULL, 0);
	NEW_PWD = _ft_strljoin("PWD=", NEW_PWD, ft_strlen(NEW_PWD));
	if (!NEW_PWD)
		return (free(OLD_PWD), EXIT_FAILURE);
	ft_mod_fevnp(OLD_PWD, main->common.f_envp);
	ft_mod_fevnp(NEW_PWD, main->common.f_envp);
	free(OLD_PWD);
	free(NEW_PWD);
	return (EXIT_SUCCESS);
}
