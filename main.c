/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:13:20 by lribette          #+#    #+#             */
/*   Updated: 2024/02/07 10:45:57 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
		write(1, "", 0);
}

static void	test_parsing(t_parsing *parse)
{
	int	i;

	i = 0;
	while (i < parse->argc)
	{
		printf("-----\n");
		printf("argv = %s\n", parse->argv[i]);
		if (parse->types[i] == 1)
			printf("types = WORD\n");
		if (parse->types[i] == 2)
			printf("types = SEPARATOR\n");
		if (parse->types[i] == 3)
			printf("types = COMMAND\n");
		if (parse->types[i] == 4)
			printf("types = OPTION\n");
		if (parse->types[i] == 5)
			printf("types = ARGUMENT\n");
		if (parse->types[i] == 6)
			printf("types = VARIABLE\n");
		if (parse->types[i] == 7)
			printf("types = PIPE\n");
		if (parse->types[i] == 8)
			printf("types = REDIRECTION\n");
		if (parse->types[i] == 9)
			printf("types = R_FILE\n");
		if (parse->types[i] == 10)
			printf("types = EQUAL\n");
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_struct	main;

	(void)argv;
	(void)envp;
	if (argc != 1)
	{
		printf("Just write \x1b[38;2;200;100;0;1m./minishell\e[0m\n");
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("\x1b[38;2;0;150;0;1mfinishell \e[5m🤯\e[0m> ");
		if (!input)
			break ;
		parsing(&main, input);
		test_parsing(&main.parse);
		ft_free_parsing(&main.parse);
	}
	return (0);
}
