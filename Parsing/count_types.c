/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:04:49 by lribette          #+#    #+#             */
/*   Updated: 2024/02/05 12:06:29 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

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
