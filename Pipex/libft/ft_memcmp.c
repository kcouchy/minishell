/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:16:30 by kcouchma          #+#    #+#             */
/*   Updated: 2023/10/24 16:21:05 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n--)
	{
		if (*(unsigned char *)s1 != *(unsigned char *)s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	return (0);
}

// int	main(void)
// {
// 	const char s1[]="noT a word";
// 	const char s2[]="not a word";
// 	size_t	n = 10;

// 	printf("%d\n", ft_memcmp(s1, s2, n));
// 	printf("%d", memcmp(s1, s2, n));
// 	return (0);
// }	