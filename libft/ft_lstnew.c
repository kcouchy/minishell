/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:43:41 by kcouchma          #+#    #+#             */
/*   Updated: 2023/10/24 14:06:17 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*add2list;

	add2list = malloc(sizeof(t_list));
	if (add2list)
	{
		add2list->content = content;
		add2list->next = NULL;
	}
	return (add2list);
}
