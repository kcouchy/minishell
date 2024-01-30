/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:40:05 by kcouchma          #+#    #+#             */
/*   Updated: 2023/10/24 11:06:55 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <bsd/string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < (size -1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
/*
int	main(void)
{
	const char src[]="";
	char dest[]="yes a word";
	const char src2[]="";
	char dest2[]="yes a word";
	size_t	n = 5;

	printf("%d\n", (int)ft_strlcpy(dest, src, n));
	printf("%d", (int)strlcpy(dest2, src2, n));
	return (0);
}
*/