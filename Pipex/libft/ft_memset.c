/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:05:36 by kcouchma          #+#    #+#             */
/*   Updated: 2023/10/17 16:35:44 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*temp;

	temp = s;
	while (n--)
	{
		*temp = (char)c;
		temp++;
	}
	return (s);
}

/*
int	main(void)
{
	char temp[] = "This ista test";
	int len;
	
	len = 6;
	printf("%s", ft_memset(temp, 65, len));
	printf("%p", ft_memset(temp, 65, len));
	return (0);
}
*/