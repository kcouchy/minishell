/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:16:21 by lribette          #+#    #+#             */
/*   Updated: 2024/03/05 08:21:34 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strndup(char *s, int start, int end, char *returned)
{
	char	*output;
	int		i;
	int		len;

	if (!s || !returned)
		return (NULL);
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

char	*var_strdup(char *f_envp)
{
	int		i;
	int		j;
	int		start;
	char	*output;

	i = 0;
	j = 0;
	start = 0;
	while (f_envp[i])
	{
		if (f_envp[i] == '=' && !start)
		{
			i++;
			start = i;
		}
		i++;
	}
	output = ft_calloc(i - start + 1, sizeof(char));
	if (output == NULL)
		return (NULL);
	while (start < i && f_envp[start])
		output[j++] = f_envp[start++];
	return (output);
}

char	*var_strjoin(char *s1, char *s2)
{
	char	*output;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
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

int	is_heredoc(char *input, int i)
{
	while (i > -1 && is_quote(input[i]))
		i--;
	while (i > -1 && is_space(input[i]))
		i--;
	if (i > -1 && input[i] == '<' && input[i - 1] == '<')
		return (1);
	return (0);
}
