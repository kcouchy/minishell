/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:01:13 by kcouchma          #+#    #+#             */
/*   Updated: 2023/10/20 09:36:47 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*temp;

	temp = dest;
	if (dest == NULL && src == NULL)
		return (dest);
	while (n--)
	{
		*temp = *(char *)src;
		temp++;
		src++;
	}
	return (dest);
}

/*
int	main(void)
{
	unsigned char source[]="yes";
	unsigned char dest[]="not a word";
	unsigned char dest2[]="not a word";
	size_t	n = 3;

	printf("%s\n", dest);
	printf("%s\n", (char *)ft_memcpy(dest, source, n));
	printf("%s", (char *)memcpy(dest2, source, n));
	return (0);
}
*/