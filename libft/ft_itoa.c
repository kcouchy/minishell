/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:00:18 by kcouchma          #+#    #+#             */
/*   Updated: 2023/10/24 11:05:37 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_n_len(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		i = 1;
	if (n < 0)
	{
		i = 1;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*fill_itoa(long n_long, size_t n_len, char *output, size_t is_neg)
{
	while (n_len > 1)
	{
		output[n_len - 1] = (n_long % 10) + '0';
		n_long = n_long / 10;
		n_len--;
	}
	if (is_neg == 1)
		output[0] = '-';
	else
		output[0] = (n_long % 10) + '0';
	return (output);
}

char	*ft_itoa(int n)
{
	char	*output;
	long	n_long;
	size_t	n_len;
	size_t	is_neg;

	n_long = n;
	n_len = ft_n_len(n_long);
	is_neg = 0;
	output = (char *)malloc(sizeof(char) * (n_len + 1));
	if (!output)
		return (NULL);
	output[n_len] = '\0';
	if (n_long < 0)
	{
		is_neg = 1;
		n_long = -n_long;
	}
	fill_itoa(n_long, n_len, output, is_neg);
	return (output);
}

// int	main(void)
// {
// 	int	n_ = -2147483648;
// 	int	n = 0;
// 	printf("neg = %d\n", ft_n_len(n_));
// 	printf("%s\n", ft_itoa(n_));
// 	printf("i_len = %d\n", ft_n_len(n));
// 	printf("%s", ft_itoa(n));
// 	return (0);
// }