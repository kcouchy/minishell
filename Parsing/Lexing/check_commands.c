/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:12:01 by lribette          #+#    #+#             */
/*   Updated: 2024/03/03 19:20:46 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

static int	_which_redirection(t_parsing *parse, int i)
{
	if (!ft_strcmp(parse->argv[i], "<")
		|| !ft_strcmp(parse->argv[i], "<<"))
		return (INPUT_REDIR);
	else if (!ft_strcmp(parse->argv[i], ">")
		|| !ft_strcmp(parse->argv[i], ">>"))
		return (OUTPUT_REDIR);
	return (0);
}

static void	_file(t_parsing *parse, int i)
{
	if (i && parse->types[i - 1] == REDIRECTION)
	{
		parse->types[i - 1] = _which_redirection(parse, i - 1);
		if (parse->types[i - 1] == INPUT_REDIR)
			parse->types[i] = INPUT_FILE;
		if (parse->types[i - 1] == OUTPUT_REDIR)
			parse->types[i] = OUTPUT_FILE;
	}
}

static int	_not_separator(t_parsing *parse, int i)
{
	if (i == 0
		|| (i && parse->types[i - 1] == PIPE && parse->types[i] != SEPARATOR))
	{
		parse->types[i] = COMMAND;
		i++;
	}
	while (i < parse->argc && parse->types[i] != SEPARATOR)
	{
		is_argument_a_command(parse, i);
		if (parse->argv[i][0] == '-' && parse->types[i] != COMMAND)
			parse->types[i] = OPTION;
		else if (parse->argv[i][0] != '-' && parse->types[i] != COMMAND)
			parse->types[i] = ARGUMENT;
		_file(parse, i);
		i++;
	}
	return (i);
}

static int	_separator(t_parsing *parse, int i)
{
	if (!ft_strcmp(parse->argv[i], "|"))
	{
		parse->number_of_commands++;
		parse->types[i] = PIPE;
	}
	else if (!ft_strcmp(parse->argv[i], "="))
		parse->types[i] = EQUAL;
	else
		parse->types[i] = REDIRECTION;
	if ((parse->argv[i + 1] && parse->types[i + 1] == SEPARATOR
		&& !(parse->types[i] == PIPE && _which_redirection(parse, i + 1)))
		|| (parse->argv[i][0] == '|' && parse->argv[i][1] == '|'))
	{
		printf("%s syntax error%s\n", RED, RESET);
		parse->error = 2;
	}
	return (i + 1);
}

void	check_commands(t_parsing *parse)
{
	int	i;

	i = 0;
	if (!ft_strcmp(parse->argv[0], "|")
		|| parse->types[parse->argc - 1] == SEPARATOR)
	{
		printf("%s syntax error%s\n", RED, RESET);
		parse->error = 2;
		return ;
	}
	while (i < parse->argc)
	{
		if (parse->error)
			return ;
		if (parse->types[i] != SEPARATOR)
			i = _not_separator(parse, i);
		if (parse->types[i] == SEPARATOR)
			i = _separator(parse, i);
	}
}
