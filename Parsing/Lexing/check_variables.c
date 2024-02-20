/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:39:03 by lribette          #+#    #+#             */
/*   Updated: 2024/02/20 15:24:46 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*_strdup(char *envp)
{
	int		i;
	int		j;
	int		start;
	char	*output;

	i = 0;
	j = 0;
	start = 0;
	while (envp[i])
	{
		if (envp[i] == '=' && !start)
		{
			i++;
			start = i;
		}
		i++;
	} 
	output = ft_calloc(i - start + 1, sizeof(char));
	if (output == NULL)
		return (NULL);
	while (start < i && envp[start])
		output[j++] = envp[start++];
	return (output);
}

char	*_strjoin(char *s1, char *s2)
{
	char	*output;
	size_t	i;
	size_t	j;

	output = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!output)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		output[i] = s2[j];
		i++;
		j++;
	}
	output[i] = '\0';
	// free(s1);
	// free(s2);
	return (output);
}

char	*ft_strndup(char *s, int start, int end, char *returned)
{
	char	*output;
	int		i;
	int		len;

	i = 0;
	len = end - start;
	output = ft_calloc(len + 1, sizeof(char));
	if (output == NULL)
		return (NULL);
	while (i < len)
	{
		output[i] = s[start];
		i++;
		start++;
	}
	if (returned)
		free(returned);
	return (output);
}

char	*copy_variable(char **envp, char *input, int start, int i)
{
	int	j;
	int	k;
	int	s;

	j = 0;
	k = 0;
	s = start;
	while (envp[j])
	{
		k = 0;
		s = start;
		// printf("envp[j] = %s\n", envp[j]);
		while (envp[j][k] && s < i && envp[j][k] == input[s++])
			k++;
		if (envp[j][k] && envp[j][k] == '=')
		{
			k++;
			char *buffer = _strdup(envp[j]);
			printf("variable = %s\n", buffer);
			// free(buffer);
			return (buffer);
		}
		j++;
	}
	return (_strdup(""));
}

// void	search_variable(t_variables *variables, char **envp, int i)
// {
	
// }

char	*check_variables(t_variables *var, char **envp, char *input)
{
	int		i;
	int		start;
	char	*variable;
	char	*buffer;

	i = 0;
	start = 0;
	buffer = NULL;
	var->str = "";
	var->left = ft_strdup(input);
	var->quote = 0;
	var->is_there_a_variable = 0;
	while (var->left[i])
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
		if (var->left[i] == '$')
		{
			var->is_there_a_variable = 1;
			start = i;
			i++;
			while (var->left[i] && (isalnum(var->left[i]) || var->left[i] == '_' || var->left[i] == '?'))
				i++;
			variable = copy_variable(envp, var->left, start + 1, i);
			buffer = ft_strndup(var->left, 0, start, buffer);
			var->str = _strjoin(var->str, buffer);
			var->str = _strjoin(var->str, variable);
			printf("var->str = %s\n", var->str);
			free(variable);
			// i = start + 1;
			var->left = ft_strndup(var->left, i, ft_strlen(var->left), var->left);
			i = 0;
			printf("var->left = %s\n", var->left);
		}
		else if (var->left[i])
			i++;
	}
	if (var->is_there_a_variable)
		var->str = _strjoin(var->str, var->left);
	printf("var->str = %s\n", var->str);
	printf("var->left = %s\n", var->left);
	if (var->str[0] == '\0')
		return (var->left);
	if (buffer)
		free(buffer);
	// free(var->str); // if buffer !
	return (var->str);
}
