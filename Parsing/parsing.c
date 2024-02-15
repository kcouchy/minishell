/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 08:58:42 by lribette          #+#    #+#             */
/*   Updated: 2024/02/15 18:58:57 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

//int	number_of_quotes()

int	parsing(t_struct *main, char *input)
{
	if (check_nothing(input))
		return (0);
	main->parse.number_of_commands = 1;
	main->parse.nb_of_inputs = 0;
	main->parse.nb_of_outputs = 0;
	main->parse.nb_of_flags = 0;
	main->parse.error = 0;
	alloc_tables(&main->parse, input);
	check_commands(&main->parse);
	// prendre le cas ou check_commands renvoit exit failure
	printf("argc = %d\n", main->parse.argc);
	main->common->nb_commands = main->parse.number_of_commands;
	if (!main->parse.error)
		main->args_list = parsing_to_executing(main);
	test_parsing(&main->parse);
	return (1);
}

// comptabiliser les guillemets
// si la ligne est tres longue -> bug d'affichage avec readline qui va recommencer au debut de la ligne

// echo -n -nnn bonjour les amis -n > test.txt | cat -e < test.txt >bonjour.txt                 >salut.txt
// echo -n bonjour -n -nn | cat -e Makefile main.c parsing.c > test.txt