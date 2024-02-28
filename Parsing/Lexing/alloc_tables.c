/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_tables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:08:23 by lribette          #+#    #+#             */
/*   Updated: 2024/02/28 16:21:32 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

int	skip_to_quote(t_parsing *parse, char *input, int i)
{
	char	quote;

	quote = '\0';
	if (is_quote(input[i]))
	{
		quote = input[i];
		i++;
		while (input[i] && input[i] != quote)
			i++;
	}
	if (quote && !input[i])
	{
		printf("%s syntax error%s\n", RED, RESET);
		parse->error = 2;
		return (i);
	}
	i++;
	return (i);
}

static int	count_tokens(t_parsing *parse, char *input)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (input[i])
	{
		while (input[i] && is_space(input[i]))
			i++;
		if (input[i] && is_separator(input[i]))
		{
			while (input[i] && input[i + 1] && input[i] == input[i + 1])
				i++;
			i++;
			counter++;
		}
		if (input[i] && !is_separator(input[i]))
		{
			while (input[i] && !is_separator(input[i]))
				i = skip_to_quote(parse, input, i);
			counter++;
		}
	}
	return (counter);
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

	parse->argc = count_tokens(parse, input);
	if (parse->error)
		return ;
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
			i = what_type(parse, input, i, 1);
		else if (input[i] && !is_separator(input[i]))
			i = what_type(parse, input, i, 0);
		j++;
	}
}
