/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 08:58:42 by lribette          #+#    #+#             */
/*   Updated: 2024/03/06 09:40:54 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"
#include "./../Pipex/pipex.h"

int	_check_nothing(char *input)
{
	int	i;

	i = 0;
	if (errno == MALLOC_ERROR)
		return (free(input), 1);
	while (input[i])
	{
		if (!is_space(input[i]))
			return (0);
		i++;
	}
	free(input);
	return (1);
}

int	_check_error(t_parsing *parse, char *input, int should_free, t_struct *main)
{
	main->exit_code = parse->error;
	if (parse->error || errno == MALLOC_ERROR)
	{
		free(input);
		if (should_free)
			ft_free_parsing(parse);
		if (errno)
			parse->error = errno;
		return (parse->error);
	}
	return (0);
}

int	parsing(t_struct *main, char *input)
{
	main->parse.number_of_commands = 1;
	main->parse.error = 0;
	if (input[0] != '\0')
		add_history(input);
	input = check_variables(&main->parse.var, main->common.f_envp, input);
	if (_check_nothing(input))
		return (NOTHING);
	alloc_tables(&main->parse, input);
	if (_check_error(&main->parse, input, 0, main))
		return (main->parse.error);
	check_commands(&main->parse);
	if (_check_error(&main->parse, input, 1, main))
		return (main->parse.error);
	builtins_parsing(&main->parse);
	main->common.nb_commands = main->parse.number_of_commands;
	free(input);
	main->args_list = parsing_to_executing(main);
	if (errno == MALLOC_ERROR)
	{
		ft_structclear(&main->args_list);
		return (errno);
	}
	return (EXIT_SUCCESS);
}
