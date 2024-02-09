/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:26:27 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/09 14:56:19 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	ft_echo(int argc, char **argv)
{
	int	i;
	int	n;

	i = 0;
	if (ft_strncmp(argv[1], "-n", 2) == 0)
		i = 1;
	n = i;
	while (i < argc)
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i++;
		if(i != argc)
			write(STDOUT_FILENO, " ", 1);
	}
	if (n == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}