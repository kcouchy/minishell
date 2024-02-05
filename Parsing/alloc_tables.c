/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_tables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:08:23 by lribette          #+#    #+#             */
/*   Updated: 2024/02/05 14:19:58 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static char	*_ft_word_dup(char *input, int start, int end)
{
	int		i;
	char	*dup;

	i = 0;
	dup = malloc((end - start + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (end > start)
		dup[i++] = input[start++];
	dup[i] = '\0';
	return (dup);
}

static int	_what_type(t_parsing *main, char *input, int i, int separator)
{
	int	start;
	int	j;

	start = i;
	j = 0;
	while (input[i] && is_separator(input[i]) == separator
		&& !is_space(input[i]))
		i++;
	while (main->types[j] != 0)
		j++;
	main->argv[j] = _ft_word_dup(input, start, i);
	if (separator)
		main->types[j] = SEPARATOR;
	else
		main->types[j] = WORD;
	return (i);
}

static void	_ft_malloc_failed(t_parsing *main, char *input)
{
	int	i;

	i = 0;
	if (!main->argv || !main->types)
	{
		printf("Malloc failed !\n");
		if (!main->argv)
		{
			while (i < main->argc)
			{
				free(main->argv[i]);
				i++;
			}
			free(main->argv);
		}
		if (!main->types)
			free(main->types);
		free(input);
		exit(EXIT_FAILURE);
	}
}

void	alloc_tables(t_parsing *main, char *input)
{
	int			i;
	int			j;

	main->argc = count_types(input);
	main->argv = ft_calloc((main->argc + 1), sizeof(char *));
	main->types = ft_calloc((main->argc + 1), sizeof(int));
	_ft_malloc_failed(main, input);
	i = 0;
	j = 0;
	while (j < main->argc)
	{
		while (input[i] && is_space(input[i]))
			i++;
		if (input[i] && is_separator(input[i]))
			i = _what_type(main, input, i, 1);
		else if (input[i] && !is_separator(input[i]))
			i = _what_type(main, input, i, 0);
		j++;
	}
}
