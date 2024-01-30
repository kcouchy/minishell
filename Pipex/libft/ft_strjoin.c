/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:59:41 by kcouchma          #+#    #+#             */
/*   Updated: 2023/10/24 11:06:35 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*output;
	size_t	i;

	output = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!output)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		output[i] = ((char *)s1)[i];
		i++;
	}
	while (*s2)
	{
		output[i] = *(char *)s2;
		i++;
		s2++;
	}
	output[i] = '\0';
	return (output);
}

// int	main(void)
// {
// 	char const s1[] = "";
// 	char const s2[] = "";
// 	printf("%s\n", ft_strjoin(s1, s2));
// 	return (0);
// }