/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:30:17 by kcouchma          #+#    #+#             */
/*   Updated: 2023/10/24 11:06:28 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == 0)
		return ((char *)s);
	return (NULL);
}

// int	main(void)
// {
// 	const char	s[]="teste";
// 	int	c = 'e';
// 	printf("%p\n", s);
// 	printf("%p", ft_strchr(s, c));
// 	return (0);
// }