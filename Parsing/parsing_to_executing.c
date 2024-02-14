/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_to_executing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:56:04 by lribette          #+#    #+#             */
/*   Updated: 2024/02/13 11:08:33 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	init_arg(t_args *cmd, t_struct *main, int start, int end)
{
	cmd->command_name = "";
	if (main->parse.argv[start])
		cmd->command_name = ft_strdup(main->parse.argv[start]);
	cmd->flags = fill_type(OPTION, main, start, end);
	cmd->input_redirs = fill_type(INPUT_REDIR, main, start, end);
	cmd->input_files = fill_type(INPUT_FILE, main, start, end);
	cmd->output_redirs = fill_type(OUTPUT_REDIR, main, start, end);
	cmd->output_files = fill_type(OUTPUT_FILE, main, start, end);
	fill_strings(cmd, main, start, end);
	cmd->is_builtin = is_builtin(cmd->command_name);
	//int		nb_of_inputs;
	//int		nb_of_outputs;
}

t_args	*ft_structnew(t_struct *main, int start, int end)
{
	t_args	*add2list;

	add2list = malloc(sizeof(t_args));
	if (add2list)
	{
		init_arg(add2list, main, start, end);
		add2list->next = NULL;
	}
	printf("\x1b[38;2;255;255;255m-----\n");
	printf("\x1b[38;2;255;0;0mwhole_cmd = %s\n", add2list->whole_cmd);
	printf("\x1b[38;2;255;132;0mcommand_name = %s\n", add2list->command_name);
	int	i = 0;
	printf("\x1b[38;2;255;216;0mflags = \n");
	while (add2list->flags[i])
	{
		printf(" -   %s\n", add2list->flags[i]);
		i++;
	}
	i = 0;
	printf("\x1b[38;2;0;255;60minput redirections = \n");
	while (add2list->input_redirs[i])
	{
		printf(" -   %s\n", add2list->input_redirs[i]);
		i++;
	}
	i = 0;
	printf("\x1b[38;2;0;144;255minput files = \n");
	while (add2list->input_files[i])
	{
		printf(" -   %s\n", add2list->input_files[i]);
		i++;
	}
	i = 0;
	printf("\x1b[38;2;0;255;60moutput redirections = \n");
	while (add2list->output_redirs[i])
	{
		printf(" -   %s\n", add2list->output_redirs[i]);
		i++;
	}
	i = 0;
	printf("\x1b[38;2;0;144;255moutput files = \n");
	while (add2list->output_files[i])
	{
		printf(" -   %s\n", add2list->output_files[i]);
		i++;
	}
	printf("\x1b[38;2;130;25;255marguments = %s\n", add2list->args);
	printf("\x1b[38;2;255;0;0mis_builtin = %d\n", add2list->is_builtin);
	return (add2list);
}

void	ft_structadd_front(t_args **commands, t_args *temp)
{
	temp->next = *commands;
	*commands = temp;
}

t_args	*parsing_to_executing(t_struct *main)
{
	t_args	*cmd;
	t_args	*temp;
	int		i;
	int		start;
	int		end;

	i = 0;
	end = 0;
	cmd = NULL;
	printf("number_of_commands = %d\n", main->parse.number_of_commands);
	while (i < main->parse.number_of_commands)
	{
		if (main->parse.types[end] == PIPE)
			end++;
		start = end;
		while (end < main->parse.argc && main->parse.types[end] != PIPE)
			end++;
		temp = ft_structnew(main, start, end);
		if (!temp)
			return (temp);
		ft_structadd_front(&cmd, temp);
		i++;
	}
	// n'oublie pas de free la liste chainee!
	return (cmd);
}
