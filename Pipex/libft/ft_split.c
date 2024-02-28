/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:13:45 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/28 14:37:12 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(char const *s, char c)
{
	int	word_count;

	word_count = 0;
	while (*s == c)
		s++;
	while (*s)
	{
		while (*s && *s != c)
			s++;
		word_count++;
		while (*s == c && *s)
			s++;
	}
	return (word_count);
}

int	ft_freetables(char **output, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		free(output[j]);
		j++;
	}
	free(output);
	return (0);
}

char	**ft_write_words(char const *s, char c, char **output, int word_count)
{
	int	i;

	i = 0;
	while (*s && i < word_count)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			output[i] = ft_substr(s, 0, (ft_strchr(s, c) - s));
			if (!output[i])
			{
				ft_freetables(output, i);
				return (NULL);
			}
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	output[i] = NULL;
	return (output);
}

char	**ft_split(char const *s, char c)
{
	char	**output;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = (ft_count_words(s, c));
	output = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!output)
		return (NULL);
	if (ft_write_words(s, c, output, word_count))
		return (output);
	return (NULL);
}

// int	main(void)
// {
// 	char const s[] = "            ";
// 	char	c = ' ';
// 	char	**output = ft_split(s, c);
// 	int		words = ft_count_words(s, c);
// 	int		i = 0;

// 	printf("%d\n", words);
// 	while (i < words)
// 	{
// 		printf("%s\n", output[i]);
// 		free(output[i]);
// 		i++;
// 	}
// 	free(output);
// 	return (0);
// }
