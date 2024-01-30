/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:14:33 by kcouchma          #+#    #+#             */
/*   Updated: 2024/01/11 15:06:18 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod2(char **argv, int fract)
{
	double	num;
	int		i;

	num = 0.;
	i = 0;
	while (**argv && **argv != '.')
	{
		num *= 10.;
		num += **argv - '0';
		(*argv)++;
		i++;
	}
	if (fract == 1)
	{
		while (i-- > 0)
			num = num / 10.;
	}
	if (num <= 2147483647 && num >= -2147483648)
		return (num);
	return (-2147483649);
}

double	ft_atod1(char *argv)
{
	double	integer;
	double	fraction;
	int		is_neg;

	integer = 0.;
	fraction = 0.;
	is_neg = -(2 * (*argv == '-') - 1);
	if (*argv == '-' || *argv == '+')
		argv++;
	integer = ft_atod2(&argv, 0);
	if (integer == -2147483649)
		return (-2147483649);
	if (*argv == '.')
		argv++;
	fraction = ft_atod2(&argv, 1);
	if (fraction == -2147483649)
		return (-2147483649);
	return (is_neg * (integer + fraction));
}
