/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:42:20 by lribette          #+#    #+#             */
/*   Updated: 2024/02/22 15:02:17 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void	builtins_parsing(t_parsing *parse)
{
	int	i;

	i = 0;
	while (parse->argv[i])
	{
		// if (parse->types[i] == COMMAND && is_builtin(parse->argv[i]))
		// {
		// 	if (!ft_strcmp(parse->argv[i], "echo"))
		// 		echo_parsing(parse, i);
		// }
		i++;
	}
}
