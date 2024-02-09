/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:13:20 by lribette          #+#    #+#             */
/*   Updated: 2024/02/09 11:37:57 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
		write(1, "", 0);
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
		if (parsing(&main, input))
			ft_free_parsing(&main.parse);
	}
	return (0);
}
