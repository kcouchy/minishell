/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:16:21 by lribette          #+#    #+#             */
/*   Updated: 2024/02/20 16:34:16 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strndup(char *s, int start, int end, char *returned)
{
	char	*output;
	int		i;
	int		len;

	i = 0;
	len = end - start;
	output = ft_calloc(len + 1, sizeof(char));
	if (output == NULL)
		return (NULL);
	while (i < len)
	{
		output[i] = s[start];
		i++;
		start++;
	}
	if (returned)
		free(returned);
	return (output);
}

char	*var_strdup(char *envp)
{
	int		i;
	int		j;
	int		start;
	char	*output;

	i = 0;
	j = 0;
	start = 0;
	while (envp[i])
	{
		if (envp[i] == '=' && !start)
		{
			i++;
			start = i;
		}
		i++;
	}
	output = ft_calloc(i - start + 1, sizeof(char));
	if (output == NULL)
		return (NULL);
	while (start < i && envp[start])
		output[j++] = envp[start++];
	return (output);
}

char	*var_strjoin(char *s1, char *s2)
{
	char	*output;
	size_t	i;
	size_t	j;

	output = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!output)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		output[i] = s2[j];
		i++;
		j++;
	}
	output[i] = '\0';
	free(s1);
	return (output);
}
