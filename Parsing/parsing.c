/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 08:58:42 by lribette          #+#    #+#             */
/*   Updated: 2024/01/31 18:06:08 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

//int	number_of_quotes()

int	is_separator(char c)
{
	if (/*c == '\''||c == '"'||*/c == '<' || c == '>' || c == '|' || c == ' ')
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
		if (is_separator(input[i]))
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

void	parsing(char *input)
{
	//t_parsing	*main;

	/*if (!input)
		return (NULL);*/
	count_types(input);
	printf("count_types = %d\n", count_types(input));
}
// comptabiliser les guillemets
// regarder le nombre de symboles identiques d'affilee
// regarder pour plusieurs symboles differents cote a cote
// malloc les tableaux