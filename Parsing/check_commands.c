/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:12:01 by lribette          #+#    #+#             */
/*   Updated: 2024/02/05 14:20:06 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static int	_not_separator(t_parsing *main, int i)
{
	if (i < main->argc && main->types[i] != SEPARATOR
		&& main->argv[i][0] != '-')
	{
		main->types[i] = COMMAND;
		i++;
	}
	while (i < main->argc && main->types[i] != SEPARATOR
		&& main->argv[i][0] == '-')
	{
		main->types[i] = OPTION;
		i++;
	}
	while (i < main->argc && main->types[i] != SEPARATOR)
	{
		main->types[i] = ARGUMENT;
		i++;
	}
	return (i);
}

static int	_separator(t_parsing *main, int i)
{
	if (i < main->argc && main->types[i] == SEPARATOR
		&& !ft_strcmp(main->argv[i], "|"))
		main->types[i] = PIPE;
	else if (i < main->argc && main->types[i] == SEPARATOR
		&& !ft_strcmp(main->argv[i], "="))
		main->types[i] = EQUAL;
	else if (i < main->argc && main->types[i] == SEPARATOR)
		main->types[i] = REDIRECTION;
	return (i + 1);
}

int	check_commands(t_parsing *main)
{
	int	i;

	i = 0;
	if (main->argv[i] && main->types[i] == SEPARATOR)
		i++;
	while (i < main->argc)
	{
		i = _not_separator(main, i);
		i = _separator(main, i);
	}
	return (0);
}
