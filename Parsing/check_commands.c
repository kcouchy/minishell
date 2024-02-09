/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:12:01 by lribette          #+#    #+#             */
/*   Updated: 2024/02/09 12:38:37 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static int	_which_redirection(t_parsing *parse, int i)
{
	if (!ft_strcmp(parse->argv[i - 1], "<")
		|| !ft_strcmp(parse->argv[i - 1], "<<"))
		return (INPUT_REDIR);
	else if (!ft_strcmp(parse->argv[i - 1], ">")
		|| !ft_strcmp(parse->argv[i - 1], ">>"))
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
		parse->types[i - 1] = _which_redirection(parse, i);
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
	return (i + 1);
}

int	check_commands(t_parsing *parse)
{
	int	i;

	i = 0;
	if (parse->types[parse->argc - 1] == SEPARATOR)
	{
		printf("%s syntax error%s\n", 
			RED, RESET);
		parse->error = 1;
		return (EXIT_FAILURE);
	}
	while (i < parse->argc)
	{
		if (parse->types[i] != SEPARATOR)
			i = _not_separator(parse, i);
		if (parse->types[i] == SEPARATOR)
			i = _separator(parse, i);
	}

	// a prendre avec des pincettes !!!
	return (0);
}
