/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:44:58 by kcouchma          #+#    #+#             */
/*   Updated: 2023/10/24 15:12:27 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		output;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (size <= ft_strlen(dst))
		output = ft_strlen(src) + size;
	else
		output = ft_strlen(dst) + ft_strlen(src);
	if (size == 0)
		return (output);
	while (dst[i])
		i++;
	while (src[j] && ((size - 1) > i))
	{
		dst[i] = ((char *)src)[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (output);
}

// #include <bsd/string.h>

// int	main(void)
// {
// 	const char src[]="a wo";
// 	char dest[]="yes ";
// 	const char src2[]="a wo";
// 	char dest2[]="yes ";
// 	size_t	n = 10;

// 	printf("%d\n", (int)ft_strlcat(dest, src, n));
// 	printf("%d", (int)strlcat(dest2, src2, n));
// 	return (0);
// }
