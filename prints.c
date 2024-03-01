/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:03:38 by lribette          #+#    #+#             */
/*   Updated: 2024/03/01 19:08:01 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_parsing(t_parsing *parse)
{
	int	i;

	i = 0;
	while (i < parse->argc)
	{
		printf("-----\n");
		printf("argv = %s\n", parse->argv[i]);
		if (parse->types[i] == WORD)
			printf("types = WORD\n");
		if (parse->types[i] == SEPARATOR)
			printf("types = SEPARATOR\n");
		if (parse->types[i] == COMMAND)
			printf("types = COMMAND\n");
		if (parse->types[i] == OPTION)
			printf("types = OPTION\n");
		if (parse->types[i] == ARGUMENT)
			printf("types = ARGUMENT\n");
		if (parse->types[i] == VARIABLE)
			printf("types = VARIABLE\n");
		if (parse->types[i] == PIPE)
			printf("types = PIPE\n");
		if (parse->types[i] == REDIRECTION)
			printf("types = REDIRECTION\n");
		if (parse->types[i] == INPUT_REDIR)
			printf("types = INPUT_REDIR\n");
		if (parse->types[i] == OUTPUT_REDIR)
			printf("types = OUTPUT_REDIR\n");
		if (parse->types[i] == INPUT_FILE)
			printf("types = INPUT_FILE\n");
		if (parse->types[i] == OUTPUT_FILE)
			printf("types = OUTPUT_FILE\n");
		if (parse->types[i] == EQUAL)
			printf("types = EQUAL\n");
		i++;
	}
}

void	test_liste_chainee(t_struct *main)
{
	t_args *temp;
	
	temp = main->args_list;
	while (temp)
	{
		printf("\x1b[38;2;255;255;255m-----\n");
		printf("\x1b[38;2;255;0;0mwhole_cmd = %s\n", temp->whole_cmd);
		int	i = 0;
		printf("\x1b[38;2;255;132;0mcommand_table = \n");
		if (!temp->command_table)
			printf(" -   (null)\n");
		else
		{
			while (temp->command_table[i])
			{
				printf(" -   %s\n", temp->command_table[i]);
				i++;
			}
		}
		if (temp->command_name)
			printf("\x1b[38;2;255;216;0mcommand_name = %s\n", temp->command_name);
		else
			printf("\x1b[38;2;255;216;0mcommand_name = (null)\n");
		i = 0;
		printf("\x1b[38;2;0;255;60mflags = \n");
		if (!temp->flags)
			printf(" -   (null)\n");
		else
		{
			while (temp->flags[i])
			{
				printf(" -   %s\n", temp->flags[i]);
				i++;
			}
		}
		i = 0;
		printf("\x1b[38;2;0;144;255minput redirections = \n");
		if (!temp->input_redirs)
			printf(" -   (null)\n");
		else
		{
			while (temp->input_redirs[i])
			{
				printf(" -   %s\n", temp->input_redirs[i]);
				i++;
			}
		}
		i = 0;
		printf("\x1b[38;2;157;31;238minput files = \n");
		if (!temp->input_files)
			printf(" -   (null)\n");
		else
		{
			while (temp->input_files[i])
			{
				printf(" -   %s\n", temp->input_files[i]);
				i++;
			}
		}
		i = 0;
		printf("\x1b[38;2;255;0;0moutput redirections = \n");
		if (!temp->output_redirs)
			printf(" -   (null)\n");
		else
		{
			while (temp->output_redirs[i])
			{
				printf(" -   %s\n", temp->output_redirs[i]);
				i++;
			}
		}
		i = 0;
		printf("\x1b[38;2;255;132;0moutput files = \n");
		if (!temp->output_files)
			printf(" -   (null)\n");
		else
		{
			while (temp->output_files[i])
			{
				printf(" -   %s\n", temp->output_files[i]);
				i++;
			}
		}
		printf("\x1b[38;2;255;216;0marguments = %s\n", temp->args);
		printf("\x1b[38;2;0;255;60mis_builtin = %d%s\n", temp->is_builtin, RESET);
		temp = temp->next;
	}
}