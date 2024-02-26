/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:10:57 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/26 19:24:33 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./../Pipex/pipex.h"

// regarde avec rien au debut de l'arg

static int	_nb_args(t_parsing *parse, int start, int end)
{
	int	counter;

	counter = 0;
	while (start != end)
	{
		if (parse->types[start] == COMMAND
			|| (parse->types[start] == ARGUMENT
			&& parse->argv[start][0] != '='))
			counter++;
		else if (parse->types[start] == ARGUMENT
			&& parse->argv[start][0] == '=')
			printf("%s export: `%s' not a valid indentifier%s\n",
			ORANGE, parse->argv[start], RESET);
		start++;
	}
	return (counter);
}

char	**export_parsing(t_struct *main, int start, int end)
{
	char	**tab;
	int		nb_of_this_type;
	int		i;

	nb_of_this_type = _nb_args(&main->parse, start, end);
	if (!nb_of_this_type)
		return (NULL);
	tab = ft_calloc((nb_of_this_type) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (start != end)
	{
		if (main->parse.types[start] == COMMAND
			|| (main->parse.types[start] == ARGUMENT
			&& main->parse.argv[start][0] != '='))
		{
			tab[i] = ft_strdup(main->parse.argv[start]);
			i++;
		}
		start++;
	}
	tab[i] = NULL;
	return (tab);
}

int	error_export(char **command_table)
{
	int	i;
	
	i = 1;
	while (command_table[i])
	{
		if (command_table[i][0] == '=')
			return (1);
		i++;
	}
	return (0);
}

// if export only, print all of envp to the terminal except the variable "_"
// copy and sort envp, (and free at the end) then in loop add declare -x add "" around the string(after = and at the end)

// if export (variable), then add "variable"+"="+"variable value" to env
// if export (variable=value), then add "variable=value" to env
// in both cases, overwrite variable if present, add if not

int ft_export(t_struct *main)
{
	int	i;

	i = 0;
	if (ft_tablen(main->args_list->command_table) == 1)
	{
		while(main->common.f_envp[i])
		{
			if (main->common.f_envp[i][0] != '_')
				write(STDOUT_FILENO, main->common.f_envp[i], ft_strlen(main->common.f_envp[i]));
			i++;
		}
	}
	return (EXIT_SUCCESS);
}