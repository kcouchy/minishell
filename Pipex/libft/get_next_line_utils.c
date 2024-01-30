/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:45:57 by kcouchma          #+#    #+#             */
/*   Updated: 2023/11/13 09:47:37 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_findnl(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strcpy(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str2[i])
	{
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
	return (str1);
}

size_t	ft_gnl_strlen(const char *c)
{
	int	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

void	*ft_gnl_calloc(size_t nmemb, size_t size)
{
	char	*output;
	size_t	i;

	i = 0;
	output = malloc(nmemb * size);
	if (output == NULL)
		return (NULL);
	while (i < nmemb)
	{
		output[i] = '\0';
		i++;
	}
	return (output);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*output;
	int		i;

	output = malloc(sizeof(char) * (ft_gnl_strlen(s1) + ft_gnl_strlen(s2) + 1));
	if (output == NULL)
		return (free(s1), NULL);
	i = 0;
	while (s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		output[i] = *s2;
		i++;
		s2++;
	}
	output[i] = '\0';
	free(s1);
	return (output);
}
