/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:59:41 by kcouchma          #+#    #+#             */
/*   Updated: 2024/03/05 21:57:55 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	_free_it(void *s1, void *s2, int freee)
{
	if (freee == 3)
		return (free(s1), free(s2));
	if (freee == 2)
		return (free(s2));
	if (freee == 1)
		return (free(s1));
	return ;
}

char	*ft_strjoinf(char const *s1, char const *s2, int freee)
{
	char	*output;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	output = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!output)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		output[i] = s2[j];
		i++;
		j++;
	}
	output[i] = '\0';
	_free_it((void *)s1, (void *)s2, freee);
	return (output);
}

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