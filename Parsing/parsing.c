/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 08:58:42 by lribette          #+#    #+#             */
/*   Updated: 2024/02/22 22:32:18 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	check_nothing(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!is_space(input[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_error(t_parsing *parse, char *input, int should_free_tables)
{
	if (parse->error)
	{
		free(input);
		if (should_free_tables)
			ft_free_parsing(parse);
		return (1);
	}
	return (0);
}

int	parsing(t_struct *main, char *input)
{
	main->parse.number_of_commands = 1;
	main->parse.error = 0;
	if (check_nothing(input))
		return (0);
	add_history(input);
	input = check_variables(&main->parse.var, main->common.envp, input);
	alloc_tables(&main->parse, input);
	if (check_error(&main->parse, input, 0))
		return (0);
	check_commands(&main->parse);
	if (check_error(&main->parse, input, 1))
		return (0);
	builtins_parsing(&main->parse);
	printf("argc = %d\n", main->parse.argc);
	main->common.nb_commands = main->parse.number_of_commands;
	test_parsing(&main->parse);
	free(input);
	main->args_list = parsing_to_executing(main);
	return (1);
}

// regarder tous les mallocs
// ecrire les commentaires de la bibliotheque

// echo -n -nnn bonjour les amis -n > test.txt | cat -e < test.txt >bonjour.txt                 >salut.txt
// echo -n bonjour -n -nn | cat -e Makefile main.c parsing.c > test.txt
// echo "$USER" '$USER' "'$USER'" '"$USER"' $? salut
// echo "'$USER'" |>bonjour.txt
