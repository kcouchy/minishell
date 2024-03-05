/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:10:57 by kcouchma          #+#    #+#             */
/*   Updated: 2024/03/05 12:54:12 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Pipex/pipex.h"

static int	_is_a_correct_export(t_parsing *parse, int i)
{
	int	j;

	j = 0;
	while (parse->argv[i][j])
	{
		if (is_space(parse->argv[i][j]))
			return (0);
		j++;
	}
	if (parse->types[i] == ARGUMENT
		&& (parse->argv[i][0] == '='
		|| !parse->argv[i][0]))
		return (0);
	return (1);
}

static int	_nb_args(t_parsing *parse, int start, int end)
{
	int	counter;

	counter = 0;
	while (start != end)
	{
		if (!_is_a_correct_export(parse, start))
			printf("%s export: `%s' not a valid indentifier%s\n",
				ORANGE, parse->argv[start], RESET);
		else
			counter++;
		start++;
	}
	return (counter);
}

char	**export_parsing(t_struct *main, int start, int end)
{
	char	**tab;
	int		nb_of_this_type;
	int		i;

	nb_of_this_type = _nb_args(&main->parse, start, end);
	if (!nb_of_this_type)
		return (NULL);
	tab = ft_calloc((nb_of_this_type) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (start != end)
	{
		if (_is_a_correct_export(&main->parse, start))
		{
			tab[i] = ft_strdup(main->parse.argv[start]);
			if (errno == MALLOC_ERROR)
				return (free_table(tab), NULL);
			i++;
		}
		start++;
	}
	tab[i] = NULL;
	return (tab);
}
