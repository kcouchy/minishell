/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 08:58:42 by lribette          #+#    #+#             */
/*   Updated: 2024/02/01 17:22:02 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

//int	number_of_quotes()

int	is_separator(char c)
{
	if (/*c == '\''||c == '"'||*/c == '<' || c == '>' || c == '|' || c == '=' || c == ' ')
		return (1);
	return (0);
}

int	count_types(char *input)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (input[i])
	{
		while (input[i] && is_separator(input[i]) && input[i] == ' ')
			i++;
		if (input[i] && is_separator(input[i]))
		{
			while (input[i] && is_separator(input[i]))
				i++;
			counter++;
		}
		if (input[i] && !is_separator(input[i]))
		{
			while (input[i] && !is_separator(input[i]))
				i++;
			counter++;
		}
	}
	return (counter);
}

char	*ft_word_dup(char *input, int start, int end)
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

int	what_type(t_parsing *main, char *input, int i, int separator)
{
	int	start;
	int	j;

	start = i;
	j = 0;
	while (input[i] && is_separator(input[i]) == separator)
		i++;
	while (main->types[j] != 0)
		j++;
	main->argv[j] = ft_word_dup(input, start, i);
	if (separator)
		main->types[j] = SEPARATOR;
	else
		main->types[j] = WORD;
	return (i);
}

void	alloc_tables(t_parsing *main, char *input)
{
	int			i;
	int			j;

	main->len = count_types(input);
	main->argv = ft_calloc((main->len + 1), sizeof(char *));
	main->types = ft_calloc((main->len + 1), sizeof(int));
	if (!main->argv || !main->types) //////////////////// ATTENTION !!!
	{
		printf("Malloc failed !\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	j = 0;
	while (j < main->len)
	{
		if (input[i] && input[i] == ' ')
			i++;
		if (input[i] && is_separator(input[i]))
			i = what_type(main, input, i, 1);
		else if (input[i] && !is_separator(input[i]))
			i = what_type(main, input, i, 0);
		j++;
	}
	//return (main);
	//main.argv = ft_calloc();
}

void	parsing(t_parsing *main, char *input)
{

	/*if (!input)
		return (NULL);*/
	alloc_tables(main, input);
	printf("count_types = %d\n", main->len);
}
// comptabiliser les guillemets
// regarder le nombre de symboles identiques d'affilee
// regarder pour plusieurs symboles differents cote a cote
// soustraire le nombre d'espaces
// malloc les tableaux