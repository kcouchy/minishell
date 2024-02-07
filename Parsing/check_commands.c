/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:12:01 by lribette          #+#    #+#             */
/*   Updated: 2024/02/07 15:33:44 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static int	_not_separator(t_parsing *parse, int i)
{
	if (parse->argv[i][0] != '-')
	{
		parse->types[i] = COMMAND;
		//parse->number_of_commands++;
		i++;
	}
	while (i < parse->argc && parse->types[i] != SEPARATOR)
	{
		if (parse->argv[i][0] == '-')
			parse->types[i] = OPTION;
		else
			parse->types[i] = ARGUMENT;
		i++;
	}
	/*while (i < parse->argc && parse->types[i] != SEPARATOR
		&& parse->argv[i][0] == '-')
	{
		parse->types[i] = OPTION;
		i++;
	}
	
	while (i < parse->argc && parse->types[i] != SEPARATOR)
	{
		parse->types[i] = ARGUMENT;
		i++;
	}*/
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
	while (i < parse->argc)
	{
		if (parse->types[i] != SEPARATOR)
			i = _not_separator(parse, i);
		if (parse->types[i] == SEPARATOR)
			i = _separator(parse, i);
	}
	i = 1;
	while (i < parse->argc)
	{
		if (parse->types[i - 1] == REDIRECTION && parse->types[i] == COMMAND)
		{
			parse->types[i] = R_FILE;
			//parse->number_of_commands--;
		}
		i++;
	}

	// a prendre avec des pincettes !!!
	if (parse->types[parse->argc - 1] == REDIRECTION)
	{
		printf("%sbash: syntax error near unexpected token `newline'%s\n", 
			RED, RESET);
		//ft_free_parse(parse);
		return (0);
		//exit(EXIT_FAILURE);
	}
	return (0);
}
