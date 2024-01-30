/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:02:22 by kcouchma          #+#    #+#             */
/*   Updated: 2023/10/18 10:57:58 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		s++;
	}
	return (NULL);
}

/*
int	main(void)
{
	unsigned char s[]="word";
	int	c = 'x';
	size_t	n = 16;

	printf("%s\n", s);
	printf("%s\n", (char *)ft_memchr(s, c, n));
	printf("%s", (char *)memchr(s, c, n));
	return (0);
}
*/