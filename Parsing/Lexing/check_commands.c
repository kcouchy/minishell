/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:12:01 by lribette          #+#    #+#             */
/*   Updated: 2024/02/13 11:09:32 by lribette         ###   ########.fr       */
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
	else
	{
		printf("%s syntax error%s\n", RED, RESET);
		parse->error = 1;
		return (0);
	}
}

static void	_file(t_parsing *parse, int i)
{
	if (i && parse->types[i - 1] == REDIRECTION)
	{
		parse->types[i - 1] = _which_redirection(parse, i - 1);
		if (parse->types[i - 1] == INPUT_REDIR)
		{
			parse->types[i] = INPUT_FILE;
			parse->nb_of_inputs++;
		}
		if (parse->types[i - 1] == OUTPUT_REDIR)
		{
			parse->types[i] = OUTPUT_FILE;
			parse->nb_of_outputs++;
		}
	}
}

static int	_not_separator(t_parsing *parse, int i)
{
	if (parse->argv[i][0] != '-' || i == 0)
	{
		parse->types[i] = COMMAND;
		_file(parse, i);
		i++;
	}
	while (i < parse->argc && parse->types[i] != SEPARATOR)
	{
		if (parse->argv[i][0] == '-')
		{
			parse->nb_of_flags++;
			parse->types[i] = OPTION;
			_file(parse, i);
		}
		else
			parse->types[i] = ARGUMENT;
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
	if (parse->argv[i + 1] && parse->types[i + 1] == SEPARATOR
		&& !(parse->types[i] == PIPE && _which_redirection(parse, i + 1)))
	{
		printf("%s syntax error%s\n", RED, RESET);
		parse->error = 1;
	}
	return (i + 1);
}

int	check_commands(t_parsing *parse)
{
	int	i;

	i = 0;
	if (!ft_strcmp(parse->argv[0], "|")
		|| parse->types[parse->argc - 1] == SEPARATOR)
	{
		printf("%s syntax error%s\n", RED, RESET);
		parse->error = 1;
		return (EXIT_FAILURE);
	}
	while (i < parse->argc)
	{
		if (parse->error)
			return (EXIT_FAILURE);
		if (parse->types[i] != SEPARATOR)
			i = _not_separator(parse, i);
		if (parse->types[i] == SEPARATOR)
			i = _separator(parse, i);
	}
	return (0);
}
