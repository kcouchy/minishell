/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:39:03 by lribette          #+#    #+#             */
/*   Updated: 2024/02/19 18:01:00 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*copy_variable(char **envp, char *input, int start, int i)
{
	int	j;
	int	k;
	int	s;

	j = 0;
	k = 0;
	s = start;
	while (envp[j])
	{
		k = 0;
		while (envp[j][k] && s < i && envp[j][k] == input[s++])
			k++;
		if (envp[j][k] && envp[j][k] == '=')
			return ()
		j++;
	}
}

char	*check_variables(char **envp, char *input)
{
	int		i;
	int		start;
	// int		nb_quotes;
	int		beginning;
	char	*buffer;

	i = 0;
	start = 0;
	beginning = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			start = i + 1;
			while (input[i] && !is_space(input[i]))
				i++;
			// buffer = ft_argjoin(/*beginning input, */
			copy_variable(envp, input, start, i);
			beginning = i;
		}
		i++;
	}
	return (input);
}
