/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:50:57 by kcouchma          #+#    #+#             */
/*   Updated: 2023/10/19 11:37:25 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*output;

	output = malloc(ft_strlen(s) + 1);
	if (output == NULL)
		return (NULL);
	ft_strlcpy(output, s, ft_strlen(s) + 1);
	return (output);
}

/*
int	main(void)
{
	const char	s[]="copy me";
	const char	*output;

	output = ft_strdup(s);
	printf("%s\n", s);
	printf("%s\n", output);
//	printf("%s\n", strdup(s));
	free((void *)output);
	return (0);
}
*/