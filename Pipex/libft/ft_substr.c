/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:06:33 by kcouchma          #+#    #+#             */
/*   Updated: 2023/10/24 11:07:17 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*temp;
	size_t	i;

	i = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	temp = malloc((len + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	while (i < len && s[i + (size_t)start])
	{
		temp[i] = (char)s[i + (size_t)start];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

// int	main(void)
// {
// 	char *temp;

// 	temp = ft_substr("", 0, 0);
// 	printf("%s", temp);
// 	free(temp);
// 	return (0);
// }