/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:53:33 by lribette          #+#    #+#             */
/*   Updated: 2024/02/13 10:54:36 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static int	_count_type(int type, t_struct *main, int start, int end)
{
	int	counter;

	counter = 0;
	while (start != end)
	{
		if (main->parse.types[start] == type)
			counter++;
		start++;
	}
	return (counter);
}

char	**fill_type(int type, t_struct *main, int start, int end)
{
	char	**tab;
	int		nb_of_this_type;
	int		i;

	nb_of_this_type = _count_type(type, main, start, end);
	tab = ft_calloc((nb_of_this_type) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (start != end)
	{
		if (main->parse.types[start] == type)
		{
			tab[i] = ft_strdup(main->parse.argv[start]);
			i++;
		}
		start++;
	}
	tab[i] = NULL;
	return (tab);
}
