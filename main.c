/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:13:20 by lribette          #+#    #+#             */
/*   Updated: 2024/02/02 18:30:34 by lribette         ###   ########.fr       */
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
			printf("types = %d\n", main.types[i]);
			i++;
		}
		ft_free_parsing(&main, input);
	}
	return (0);
}
