/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:13:20 by lribette          #+#    #+#             */
/*   Updated: 2024/02/04 13:38:58 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_parsing(t_parsing *main, char *input)
{
	int	i;
	
	i = 0;
	while (i < main->len)
	{
		free(main->argv[i]);
		i++;
	}
	free(main->argv);
	free(main->types);
	free(input);
}

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
		write(1, "", 0);
}

int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_parsing	main;
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
		int i = 0;
		while (i < main.len)
		{
			printf("-----\n");
			printf("argv = %s\n", main.argv[i]);
			if (main.types[i] == 1)
				printf("types = WORD\n");
			if (main.types[i] == 2)
				printf("types = SEPARATOR\n");
			if (main.types[i] == 3)
				printf("types = COMMAND\n");
			if (main.types[i] == 4)
				printf("types = OPTION\n");
			if (main.types[i] == 5)
				printf("types = ARGUMENT\n");
			if (main.types[i] == 6)
				printf("types = VARIABLE\n");
			i++;
		}
		ft_free_parsing(&main, input);
	}
	return (0);
}
