/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:26:27 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/22 18:31:06 by lribette         ###   ########.fr       */
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