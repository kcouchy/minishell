/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:50:23 by kcouchma          #+#    #+#             */
/*   Updated: 2024/03/05 16:16:48 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Pipex/pipex.h"

int	exit_parsing(t_parsing *parse, int i)
{
	while (parse->argv[i] && parse->types[i] != PIPE)
	{
		if (parse->types[i] == OPTION)
			parse->types[i] = ARGUMENT;
		i++;
	}
	return (i);
}

static int	_error(char *str)
{
	ft_write_join(ORANGE, " exit: ", str, ": numeric argument required");
	if (errno == MALLOC_ERROR)
		return (errno);
	return (SYNTAX_ERROR);
}

int	exit_atoi(char *str)
{
	int					i;
	unsigned long long	integer;
	int					nega;

	i = 0;
	integer = 0;
	nega = 1;
	if (str[i] == '-')
	{
		nega = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		integer = integer * 10 + str[i++] - 48;
		if (integer > 9223372036854775807
			&& ft_strcmp(str, "-9223372036854775808"))
			return (_error(str));
	}
	if (str[i] || !ft_strcmp(str, "-"))
		return (_error(str));
	return ((integer * nega) % 256);
}

void	ft_exit(t_pipex *pipex, t_struct *main, t_args *arg)
{
	int	exit_code;

	exit_code = 0;
	if (pipex->pid != 0)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (arg->args)
		exit_code = exit_atoi(arg->command_table[1]);
	ft_exit_error(pipex, main, exit_code);
}
