/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:24:02 by kcouchma          #+#    #+#             */
/*   Updated: 2023/10/19 18:04:02 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (src > dest)
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else if (dest > src)
	{
		while (n-- > 0)
		{
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
		}
	}
	return (dest);
}

/*
int	main(void)
{
	const char src[]="noT a word";
	const char dest[]="";
	const char src2[]="noT a word";
	const char dest2[]="";
	size_t	n = 1;

	printf("%s\n", (char *)ft_memmove((void *)dest, src, n));
	printf("%s", (char *)memmove((void *)dest2, src2, n));
	return (0);
}
*/