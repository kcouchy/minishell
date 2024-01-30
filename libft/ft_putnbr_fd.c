/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:00:52 by kcouchma          #+#    #+#             */
/*   Updated: 2023/11/02 16:39:09 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(long n, int fd)
{
	char		c;
	int			count;

	count = 1;
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
		count++;
	}
	if (n >= 10)
		count += ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
	return (count);
}
