/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:35:22 by kcouchma          #+#    #+#             */
/*   Updated: 2023/10/17 14:41:48 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	is_neg;
	int	output;

	i = 0;
	is_neg = 1;
	output = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			is_neg = -is_neg;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		output = output * 10;
		output = output + nptr[i] - 48;
		i++;
	}
	output = output * is_neg;
	return (output);
}
