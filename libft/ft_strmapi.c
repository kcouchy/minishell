/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:53:32 by kcouchma          #+#    #+#             */
/*   Updated: 2023/10/24 11:37:38 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*output;

	i = 0;
	output = malloc ((ft_strlen(s) + 1) * sizeof(char));
	if (!output)
		return (NULL);
	while (s[i])
	{
		output[i] = f(i, s[i]);
		i++;
	}
	output [i] = '\0';
	return (output);
}
