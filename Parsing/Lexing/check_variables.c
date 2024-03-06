/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:39:03 by lribette          #+#    #+#             */
/*   Updated: 2024/03/06 09:29:32 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*_copy_variable(char **f_envp, char *input, int start, int i)
{
	int		j;
	int		k;
	int		s;

	if (!input)
		return (NULL);
	if (!f_envp)
		return (var_strdup(""));
	j = 0;
	while (f_envp[j])
	{
		k = 0;
		s = start;
		while (f_envp[j][k] && s < i && f_envp[j][k] == input[s])
		{
			s++;
			k++;
		}
		if (f_envp[j][k] && f_envp[j][k] == '=' && s == i)
			return (var_strdup(f_envp[j]));
		j++;
	}
	return (var_strdup(""));
}

static int	_search_variable(t_variables *var, char **f_envp, int i)
{
	int		start;
	char	*buffer;
	char	*variable;

	var->is_there_a_variable = 1;
	start = i - 1;
	buffer = ft_strdup("");
	while (var->left[i] && (isalnum(var->left[i])
			|| var->left[i] == '_' || var->left[i] == '?'))
		i++;
	variable = _copy_variable(f_envp, var->left, start + 1, i);
	buffer = ft_strndup(var->left, 0, start, buffer);
	if (i == start + 1)
		buffer = var_strjoin(buffer, "$");
	var->str = var_strjoin(var->str, buffer);
	var->str = var_strjoin(var->str, variable);
	if (variable)
		free(variable);
	var->left = ft_strndup(var->left, i, ft_strlen(var->left), var->left);
	if (buffer)
		free(buffer);
	return (0);
}

static int	_check_quotes(t_variables *var, int i)
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

static void	_replace_input(t_variables *var, char **f_envp)
{
	int		i;

	i = 0;
	while (var->left[i])
	{
		i = _check_quotes(var, i);
		if (var->left[i] == '$' && !is_heredoc(var->left, i - 1))
		{
			i = _search_variable(var, f_envp, i + 1);
			if (errno == MALLOC_ERROR)
				return ;
		}
		else if (var->left[i])
			i++;
	}
	if (var->is_there_a_variable)
		var->str = var_strjoin(var->str, var->left);
}

char	*check_variables(t_variables *var, char **f_envp, char *input)
{
	var->left = ft_strdup(input);
	free(input);
	if (errno == MALLOC_ERROR)
		return (NULL);
	var->str = ft_strdup("");
	if (errno == MALLOC_ERROR)
		return (err_str(var->left, NULL, NULL, NULL));
	var->quote = 0;
	var->is_there_a_variable = 0;
	_replace_input(var, f_envp);
	if (errno == MALLOC_ERROR)
		return (err_str(var->str, var->left, NULL, NULL));
	if (var->str[0] == '\0')
	{
		free(var->str);
		return (var->left);
	}
	free(var->left);
	return (var->str);
}
