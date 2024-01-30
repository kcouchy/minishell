/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:19:13 by kcouchma          #+#    #+#             */
/*   Updated: 2023/10/24 11:07:12 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*output;
	size_t	len;

	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (*s1 && ft_strchr(set, s1[len - 1]))
		len--;
	output = malloc(sizeof(char) * (len + 1));
	if (!output)
		return (NULL);
	ft_memcpy(output, s1, len);
	output[len] = '\0';
	return (output);
}

// int	main(void)
// {
// 	char const	s1[] = "sssaaaabbbbbaaasss";
// 	char const	set[] = "abs";

// 	printf("%s", ft_strtrim(s1, set));
// 	return (0);
// }