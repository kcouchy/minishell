/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:57:46 by lribette          #+#    #+#             */
/*   Updated: 2024/03/05 12:08:00 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

int	is_separator(char c)
{
	if (c == '<' || c == '>' || c == '|' || is_space(c))
		return (1);
	return (0);
}

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	is_argument_a_command(t_parsing *parse, int i)
{
	int	j;

	j = i;
	while (j > -1)
	{
		if (parse->types[j] == PIPE)
			break ;
		if (parse->types[j] == COMMAND)
			return ;
		j--;
	}
	parse->types[i] = COMMAND;
}
