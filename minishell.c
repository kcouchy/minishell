/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:13:20 by lribette          #+#    #+#             */
/*   Updated: 2024/02/15 12:21:38 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# include "./Pipex/pipex.h"

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line(); //needed to reshow prompt
		rl_replace_line("", 1); //empties readline buffer in case there's something before the ^C
		rl_redisplay(); //effectively forces the prompt to redisplay before you type
	}
	//set exitcode to 130 (will need a global variable to stock this)
}

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

char **finishell_env(char **envp)
{
	char	**f_envp;
	int		i;

	f_envp = NULL;
	i = 0;
	while (envp[i])
		i++;
	f_envp = ft_calloc(i + 1, sizeof(char *));
	if (!f_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		f_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	return (f_envp);
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
		printf("\x1b[38;2;255;216;0mcommand_table = \n");
		while (temp->command_table[i])
		{
			printf(" -   %s\n", temp->command_table[i]);
			i++;
		}
		printf("\x1b[38;2;255;132;0mcommand_name = %s\n", temp->command_name);
		i = 0;
		printf("\x1b[38;2;255;216;0mflags = \n");
		while (temp->flags[i])
		{
			printf(" -   %s\n", temp->flags[i]);
			i++;
		}
		i = 0;
		printf("\x1b[38;2;0;255;60minput redirections = \n");
		while (temp->input_redirs[i])
		{
			printf(" -   %s\n", temp->input_redirs[i]);
			i++;
		}
		i = 0;
		printf("\x1b[38;2;0;144;255minput files = \n");
		while (temp->input_files[i])
		{
			printf(" -   %s\n", temp->input_files[i]);
			i++;
		}
		i = 0;
		printf("\x1b[38;2;0;255;60moutput redirections = \n");
		while (temp->output_redirs[i])
		{
			printf(" -   %s\n", temp->output_redirs[i]);
			i++;
		}
		i = 0;
		printf("\x1b[38;2;0;144;255moutput files = \n");
		while (temp->output_files[i])
		{
			printf(" -   %s\n", temp->output_files[i]);
			i++;
		}
		printf("\x1b[38;2;130;25;255marguments = %s\n", temp->args);
		printf("\x1b[38;2;255;0;0mis_builtin = %d\n", temp->is_builtin);
		temp = temp->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_struct	main;

	(void)argv;
	if (argc != 1)
	{
		printf("Just write \x1b[38;2;200;100;0;1m./minishell\e[0m\n");
		exit(EXIT_FAILURE);
	}
	//use sigaction
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	main.common->envp = finishell_env(envp);
	while (1)
	{
		input = readline(GREEN"finishell \e[5m🤯"RESET GREEN"> "RESET);
		if (!input)
			break ;
		if (parsing(&main, input))
		{
			test_liste_chainee(&main);
			ft_free_parsing(&main.parse);
			// executing(argc, argv, envp, 2);
			//executing(&main.args, envp, 2);
			executing(&main);
		}
	}
	return (0);
}
