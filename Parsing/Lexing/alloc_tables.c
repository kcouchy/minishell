/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_tables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:08:23 by lribette          #+#    #+#             */
/*   Updated: 2024/02/17 20:45:02 by lribette         ###   ########.fr       */
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
		parse->error = 1;
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
			{
				// char quote = '\0';
				// if (is_quote(input[i]))
				// {
				// 	quote = input[i];
				// 	i++;
				// 	while (input[i] && input[i] != quote)
				// 		i++;
				// }
				// i++;
				i = skip_to_quote(parse, input, i);
				if (parse->error)
					return(counter);
			}
			counter++;
		}
	}
	return (counter);
}

static char	*_ft_word_dup(char *input, int start, int end, int nb_of_quotes)
{
	int		i;
	char	*dup;
	char	quote;

	i = 0;
	dup = ft_calloc((end - start - nb_of_quotes + 1), sizeof(char));
	quote = '\0';
	if (!dup)
		return (NULL);
	while (end > start)
	{
		if (!quote && is_quote(input[start]))
		{
			quote = input[start];
			start++;
		}
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

static int	_what_type(t_parsing *parse, char *input, int i, int separator)
{
	int		start;
	int		j;
	char	quote;
	int		nb_of_quotes;

	start = i;
	j = 0;
	quote = '\0';
	nb_of_quotes = 0;
	while (input[i] && !is_space(input[i]))
	{
		if (!separator && is_quote(input[i]))
		{
			quote = input[i];
			nb_of_quotes++;
			i++;
			while (input[i] && input[i] != quote)
				i++;
			nb_of_quotes++;
		}
		if (input[i] && is_space(input[i]))
			break ;
		i++;
		if (input[i] && separator && input[i - 1] != input[i])
			break ;
		if (is_separator(input[i]) != separator)
			break ;
	}
	// printf("%snb_of_quotes = %d\n", RED, nb_of_quotes);
	while (parse->types[j] != 0)
		j++;
	parse->argv[j] = _ft_word_dup(input, start, i, nb_of_quotes);
	if (separator)
		parse->types[j] = SEPARATOR;
	else
		parse->types[j] = WORD;
	return (i);
}

// static int	_what_type(t_parsing *parse, char *input, int i, int separator)
// {
// 	int	start;
// 	int	j;

// 	start = i;
// 	j = 0;
// 	while (input[i] && !is_space(input[i]))
// 	{
// 		i++;
// 		if (input[i] && separator && input[i - 1] != input[i])
// 			break ;
// 		if (is_separator(input[i]) != separator)
// 			break ;
// 	}
// 	while (parse->types[j] != 0)
// 		j++;
// 	parse->argv[j] = _ft_word_dup(input, start, i);
// 	if (separator)
// 		parse->types[j] = SEPARATOR;
// 	else
// 		parse->types[j] = WORD;
// 	return (i);
// }

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
			i = _what_type(parse, input, i, 1);
		else if (input[i] && !is_separator(input[i]))
			i = _what_type(parse, input, i, 0);
		j++;
	}
}
