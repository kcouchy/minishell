/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:26:27 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/23 16:31:35 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./../Pipex/pipex.h"

int	echo_parsing(t_parsing *parse, int i)
{
	int	arg;
	int	j;

	arg = 0;
	j = 1;
	while (parse->argv[i] && parse->types[i] != PIPE)
	{
		j = 1;
		if (!arg)
		{
			if (parse->types[i] == OPTION)
			{
				while (parse->argv[i][j] && parse->argv[i][j] == 'n')
					j++;
			}
			if (j == 1 || parse->argv[i][j] || parse->types[i] == ARGUMENT)
				arg = 1;
		}
		if (arg && parse->types[i] == OPTION)
			parse->types[i] = ARGUMENT;
		i++;
	}
	return (i);
}

int	ft_echo(t_args *arg)
{
	if (arg->args)
		ft_putstr_fd(arg->args, STDOUT_FILENO);
	if (!arg->flags)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
