/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fenvp_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:43:41 by kcouchma          #+#    #+#             */
/*   Updated: 2024/03/06 09:17:33 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Pipex/pipex.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	if (tab)
		while (tab[i])
			i++;
	return (i);
}

int	ft_find_eq(char *f_envp)
{
	int	i;

	i = 0;
	while (f_envp[i] && f_envp[i] != '=')
		i++;
	return (i);
}

int	find_arg(char *arg, char **f_envp)
{
	int	i;

	i = 0;
	if (!f_envp)
		return (-1);
	while (f_envp[i])
	{
		if (strncmp(arg, f_envp[i], ft_find_eq(arg)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**ft_realloc(char **tab)
{
	int		i;
	int		len;
	char	**output;

	i = 0;
	len = ft_tablen(tab);
	output = malloc(sizeof(char *) * (len + 2));
	if (!output)
		return (NULL);
	while (i < len)
	{
		output[i] = tab[i];
		i++;
	}
	output[i] = NULL;
	output[i + 1] = NULL;
	if (tab)
		free(tab);
	return (output);
}

int	ft_mod_fevnp(char *arg, char ***f_envp)
{
	int	i;
	int	j;

	i = find_arg(arg, *f_envp);
	if (i != -1)
	{
		if (ft_strlen(arg) == (size_t)ft_find_eq(arg))
			return (EXIT_SUCCESS);
		free((*f_envp)[i]);
		(*f_envp)[i] = ft_strdup(arg);
		if (!(*f_envp)[i])
			return (EXIT_FAILURE);
	}
	else
	{
		*f_envp = ft_realloc(*f_envp);
		j = ft_tablen(*f_envp);
		(*f_envp)[j] = ft_strdup(arg);
		if (!(*f_envp)[j])
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
