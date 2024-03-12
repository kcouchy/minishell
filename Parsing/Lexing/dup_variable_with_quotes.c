/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_variable_with_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:10:48 by lribette          #+#    #+#             */
/*   Updated: 2024/03/12 17:12:20 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*_ft_strndup(char *s, int start, int end)
{
	char	*output;
	int		i;
	int		len;

	if (!s)
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
	return (output);
}

char	*_dup_with_quotes_around(char *str, char *output, int start, int end)
{
	int		i;

	if (!str || !output)
		return (NULL);
	i = 0;
	output = ft_strjoinf(output, "\"", 1);
	output = ft_strjoinf(output, _ft_strndup(str, start, end), 3);
	output = ft_strjoinf(output, "\"", 1);
	return (output);
}

static int	_skip_spaces(char *str, int start, int space)
{
	if (!str)
		return (0);
	while (str[start] && is_space(str[start]) == space)
		start++;
	return (start);
}

char	*dup_variable_with_quotes(char *str)
{
	int		start;
	int		i;
	char	*output;

	output = ft_strdup("");
	i = 0;
	start = 0;
	while (str[i] && str[start])
	{
		start = _skip_spaces(str, i, 1);
		output = ft_strjoinf(output, _ft_strndup(str, i, start), 3);
		i = _skip_spaces(str, start, 0);
		output = _dup_with_quotes_around(str, output, start, i);
	}
	free(str);
	return (output);
}
