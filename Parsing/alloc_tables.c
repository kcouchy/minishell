/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_tables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:08:23 by lribette          #+#    #+#             */
/*   Updated: 2024/02/09 12:56:13 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static char	*_ft_word_dup(char *input, int start, int end)
{
	int		i;
	char	*dup;

	i = 0;
	dup = ft_calloc((end - start + 1), sizeof(char));
	if (!dup)
		return (NULL);
	while (end > start)
		dup[i++] = input[start++];
	dup[i] = '\0';
	return (dup);
}

static int	_what_type(t_parsing *parse, char *input, int i, int separator)
{
	int	start;
	int	j;

	start = i;
	j = 0;
	while (input[i] && is_separator(input[i]) == separator
		&& !is_space(input[i]))
		i++;
	while (parse->types[j] != 0)
		j++;
	parse->argv[j] = _ft_word_dup(input, start, i);
	if (separator)
		parse->types[j] = SEPARATOR;
	else
		parse->types[j] = WORD;
	return (i);
}

static void	_ft_malloc_failed(t_parsing *parse)
{
	int	i;

	i = 0;
	if (!parse->argv || !parse->types)
	{
		printf("%s Malloc failed !\n%s", RED, RESET);
		if (!parse->argv)
		{
			while (i < parse->argc)
			{
				free(parse->argv[i]);
				i++;
			}
			free(parse->argv);
		}
		if (!parse->types)
			free(parse->types);
		exit(EXIT_FAILURE);
	}
}

void	alloc_tables(t_parsing *parse, char *input)
{
	int			i;
	int			j;

	parse->argc = count_types(input);
	parse->argv = ft_calloc((parse->argc + 1), sizeof(char *));
	parse->types = ft_calloc((parse->argc + 1), sizeof(int));
	_ft_malloc_failed(parse);
	i = 0;
	j = 0;
	while (j < parse->argc)
	{
		while (input[i] && is_space(input[i]))
			i++;
		if (input[i] && is_separator(input[i]))
			i = _what_type(parse, input, i, 1);
		else if (input[i] && !is_separator(input[i]))
			i = _what_type(parse, input, i, 0);
		j++;
	}
}
