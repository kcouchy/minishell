/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:39:03 by lribette          #+#    #+#             */
/*   Updated: 2024/02/24 09:46:33 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*copy_variable(char **f_envp, char *input, int start, int i)
{
	int		j;
	int		k;
	int		s;

	j = 0;
	k = 0;
	s = start;
	while (f_envp[j])
	{
		k = 0;
		s = start;
		while (f_envp[j][k] && s < i && f_envp[j][k] == input[s++])
			k++;
		if (f_envp[j][k] && f_envp[j][k] == '=')
		{
			k++;
			return (var_strdup(f_envp[j]));
		}
		j++;
	}
	return (var_strdup(""));
}

int	search_variable(t_variables *var, char **f_envp, int i)
{
	int		start;
	char	*buffer;
	char	*variable;

	var->is_there_a_variable = 1;
	start = i - 1;
	buffer = NULL;
	while (var->left[i] && (isalnum(var->left[i])
			|| var->left[i] == '_' || var->left[i] == '?'))
		i++;
	variable = copy_variable(f_envp, var->left, start + 1, i);
	buffer = ft_strndup(var->left, 0, start, buffer);
	if (i == start + 1)
		buffer = var_strjoin(buffer, "$");
	var->str = var_strjoin(var->str, buffer);
	var->str = var_strjoin(var->str, variable);
	free(variable);
	var->left = ft_strndup(var->left, i, ft_strlen(var->left), var->left);
	if (buffer)
		free(buffer);
	return (0);
}

int	check_quotes(t_variables *var, int i)
{
	if (var->left[i] && var->left[i] == '"')
	{
		if (!var->quote)
			var->quote = 1;
		else
			var->quote = 0;
	}
	if (var->left[i] == '\'' && !var->quote)
	{
		i++;
		while (var->left[i] && var->left[i] != '\'')
			i++;
	}
	return (i);
}

int	is_heredoc(char *input, int i)
{
	while (i > -1 && is_quote(input[i]))
		i--;
	while (i > -1 && is_space(input[i]))
		i--;
	if (i > -1 && input[i] == '<' && input[i - 1] == '<')
		return (1);
	return (0);
}

char	*check_variables(t_variables *var, char **f_envp, char *input)
{
	int		i;

	i = 0;
	var->str = ft_strdup("");
	var->left = ft_strdup(input);
	var->quote = 0;
	var->is_there_a_variable = 0;
	while (var->left[i])
	{
		i = check_quotes(var, i);
		if (var->left[i] == '$' && !is_heredoc(var->left, i - 1))
			i = search_variable(var, f_envp, i + 1);
		else if (var->left[i])
			i++;
	}
	if (var->is_there_a_variable)
		var->str = var_strjoin(var->str, var->left);
	if (var->str[0] == '\0')
	{
		free(var->str);
		return (var->left);
	}
	free(var->left);
	return (var->str);
}
