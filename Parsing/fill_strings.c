/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:41:09 by lribette          #+#    #+#             */
/*   Updated: 2024/02/19 17:43:12 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

char	*ft_argjoin(char *s1, char *s2)
{
	char	*output;
	int		i;

	output = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 2), sizeof(char));
	if (!output)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		output[i] = *s2;
		i++;
		s2++;
	}
	output[i] = ' ';
	output[i + 1] = '\0';
	if (s1[0])
		free(s1);
	return (output);
}

static char	*_remove_space(char *str)
{
	int		i;
	int		len;
	char	*s;

	i = 0;
	len = ft_strlen(str) - 1;
	s = ft_calloc(len + 1, sizeof(char));
	while (i < len)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	free(str);
	return (s);
}

void	fill_strings(t_args *cmd, t_struct *main, int start, int end)
{
	int	number_of_args;

	number_of_args = 0;
	cmd->whole_cmd = "";
	cmd->args = "";
	while (start != end)
	{
		cmd->whole_cmd = ft_argjoin(cmd->whole_cmd, main->parse.argv[start]);
		if (main->parse.types[start] == ARGUMENT)
		{
			cmd->args = ft_argjoin(cmd->args, main->parse.argv[start]);
			number_of_args++;
		}
		start++;
	}
	if (cmd->whole_cmd[0])
		cmd->whole_cmd = _remove_space(cmd->whole_cmd);
	if (number_of_args)
		cmd->args = _remove_space(cmd->args);
	if (!ft_strcmp(cmd->args, ""))
		cmd->args = NULL;
}
