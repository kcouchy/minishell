/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:44:46 by lribette          #+#    #+#             */
/*   Updated: 2024/02/21 14:24:13 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_free_parsing(t_parsing *parse)
{
	int	i;

	i = 0;
	while (i < parse->argc)
	{
		free(parse->argv[i]);
		i++;
	}
	free(parse->argv);
	free(parse->types);
}

static void	_free_table(char	**tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
	}
	free(tab);
}

static void	_free_command(t_args *cmd)
{
	free(cmd->whole_cmd);
	_free_table(cmd->command_table);
	if (cmd->command_name)
		free(cmd->command_name);
	_free_table(cmd->flags);
	if (cmd->args)
		free(cmd->args);
	_free_table(cmd->input_redirs);
	_free_table(cmd->input_files);
	_free_table(cmd->output_redirs);
	_free_table(cmd->output_files);
	if (cmd->input)
		free(cmd->input);
	if (cmd->output)
		free(cmd->output);
	free(cmd);
}

void	ft_structclear(t_args **cmd)
{
	t_args	*temp;

	if (*cmd)
	{
		while (*cmd)
		{
			temp = (*cmd)->next;
			_free_command(*cmd);
			*cmd = temp;
		}
	}
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	if (envp)
	{
		while (envp[i])
		{
			free(envp[i]);
			i++;
		}
		free(envp);
	}
}
