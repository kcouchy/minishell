/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:53:44 by lribette          #+#    #+#             */
/*   Updated: 2024/03/03 11:30:57 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

static int	_calculating_gap(char *input, int i, int *nb_quotes, int separator)
{
	char	quote;

	quote = '\0';
	while (input[i] && !is_space(input[i]))
	{
		if (!separator && is_quote(input[i]))
		{
			quote = input[i];
			*nb_quotes += 1;
			i++;
			while (input[i] && input[i] != quote)
				i++;
			*nb_quotes += 1;
		}
		if (input[i] && is_space(input[i]))
			break ;
		i++;
		if (input[i] && separator && input[i - 1] != input[i])
			break ;
		if (is_separator(input[i]) != separator)
			break ;
	}
	return (i);
}

static char	*_ft_word_dup(char *input, int start, int end, int nb_of_quotes)
{
	int		i;
	char	*dup;
	char	quote;

	i = 0;
	quote = '\0';
	dup = ft_calloc((end - start - nb_of_quotes + 1), sizeof(char));
	if (!dup)
		return (NULL);
	while (end > start)
	{
		if (!quote && is_quote(input[start]))
			quote = input[start++];
		if (input[start] != quote)
			dup[i++] = input[start++];
		if (quote && input[start] == quote)
		{
			quote = '\0';
			start++;
		}
	}
	dup[i] = '\0';
	return (dup);
}

int	what_type(t_parsing *parse, char *input, int i, int separator)
{
	int		start;
	int		j;
	int		nb_of_quotes;

	start = i;
	j = 0;
	nb_of_quotes = 0;
	i = _calculating_gap(input, i, &nb_of_quotes, separator);
	while (parse->types[j] != 0)
		j++;
	parse->argv[j] = _ft_word_dup(input, start, i, nb_of_quotes);
	if (separator)
		parse->types[j] = SEPARATOR;
	else
		parse->types[j] = WORD;
	return (i);
}
