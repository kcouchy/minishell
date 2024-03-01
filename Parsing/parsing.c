/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 08:58:42 by lribette          #+#    #+#             */
/*   Updated: 2024/03/01 09:36:51 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"
#include "./../Pipex/pipex.h"

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
	free(input);
	return (1);
}

int	check_error(t_parsing *parse, char *input, int should_free, t_struct *main)
{
	main->exit_code = parse->error;
	if (parse->error)
	{
		free(input);
		if (should_free)
			ft_free_parsing(parse);
		return (1);
	}
	return (0);
}

/*void	check_exit(t_struct *main)
{
	int		exit_code;
	t_pipex	pipex;

	exit_code = 0;
	if (main->parse.number_of_commands == 1
		&& main->args_list->command_name
		&& !ft_strcmp(main->args_list->command_name, "exit"))
	{
		write(1, "exit\n", 5);
		ft_redirections(&pipex, main);
		ft_free_parsing(&main->parse);
		ft_structclear(&main->args_list);
		rl_clear_history();
		free_envp(main->common.f_envp);
		exit(exit_code);
	}
}*/

int	parsing(t_struct *main, char *input)
{
	char	*input2;

	main->parse.number_of_commands = 1;
	main->parse.error = 0;
	if (check_nothing(input))
		return (NOTHING);
	add_history(input);
	input2 = check_variables(&main->parse.var, main->common.f_envp, input);
	free(input);
	alloc_tables(&main->parse, input2);
	if (check_error(&main->parse, input2, 0, main))
		return (SYNTAX_ERROR);
	check_commands(&main->parse);
	if (check_error(&main->parse, input2, 1, main))
		return (SYNTAX_ERROR);
	builtins_parsing(&main->parse);
	main->common.nb_commands = main->parse.number_of_commands;
	// test_parsing(&main->parse);
	free(input2);
	main->args_list = parsing_to_executing(main);
	// check_exit(main);
	return (EXIT_SUCCESS);
}

// regarder tous les mallocs
// ecrire les commentaires de la bibliotheque

// echo -n -nnn bonjour les amis -n > test.txt | cat -e < test.txt >bonjour.txt                 >salut.txt
// echo -n bonjour -n -nn | cat -e Makefile main.c parsing.c > test.txt
// echo "$USER" '$USER' "'$USER'" '"$USER"' $? salut
// echo "'$USER'" |>bonjour.txt
