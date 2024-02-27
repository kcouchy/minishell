/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:10:57 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/27 18:39:33 by kcouchma         ###   ########.fr       */
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

static int	_sorted(char **ex)
{
	int	i;

	i = 0;
	while (ex[i] && ex[i + 1])
	{
		if (ft_strncmp(ex[i], ex[i + 1], ft_strlen(ex[i])) > 0)
			return (1) ;
		i++;
	}
	return (0);
}

static void	_sort_export(char **ex)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (_sorted(ex))
	{
		while (ex[i] && ex[i + 1])
		{
			ft_strncmp(ex[i], ex[i + 1], 5);
			if (ft_strncmp(ex[i], ex[i + 1], ft_strlen(ex[i])) > 0)
			{
				temp = ex[i];
				ex[i] = ex[i + 1];
				ex[i + 1] = temp;
				temp = NULL;
			}
			i++;
		}
		i = 0;
	}
}

static int	_print_export(char **f_envp)
{
	int		i;
	char	**export;

	i = 0;
	export = malloc(sizeof(char *) * (ft_tablen(f_envp) + 1));
	if (!export)
		return (EXIT_FAILURE);
	while (f_envp[i])
	{
		export[i] = ft_strdup(f_envp[i]);
		if (!export[i])
			return (ft_freetable(export), EXIT_FAILURE);
		i++;
	}
	export[i] = NULL;
	_sort_export(export);
	i = 0;
	while (export[i])
	{
		if (export[i][0] != '_')
		{
			write(STDOUT_FILENO, export[i], ft_strlen(export[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		i++;
	}
	return (ft_freetable(export), EXIT_SUCCESS);
}

static int	_find_eq(char *f_envp)
{
	int	i;

	i = 0;
	while (f_envp[i] && f_envp[i] != '=')
		i++;
	return (i);
}

static int	_find_arg(char *arg, char **f_envp)
{
	int	i;

	i = 0;
	while (f_envp[i])
	{
		if (strncmp(arg, f_envp[i], _find_eq(arg)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int ft_export(t_args *arg, t_struct *main)
{
	char	**f_envp;
	char	**cmdtab;
	int		i;
	int		j;

	f_envp = main->common.f_envp;
	cmdtab = arg->command_table;
	if (!arg->args)
		exit(_print_export(f_envp));
	i = 0;
	j = 1;
	while (cmdtab[j])
	{
		i = _find_arg(cmdtab[j], f_envp);
		if (i != -1)
		{
			free(f_envp[i]);
			f_envp[i] = ft_strdup(cmdtab[j]);
			if (!f_envp[i])
				return (EXIT_FAILURE);
		}
		else
		{
			f_envp[ft_tablen(f_envp)] = ft_strdup(cmdtab[j]);
			if (!f_envp[ft_tablen(f_envp)])
				return (EXIT_FAILURE);
			f_envp[ft_tablen(f_envp) + 1] = malloc(sizeof(char *) * 1);
			f_envp[ft_tablen(f_envp) + 1] = NULL;
		}
		j++;
	}
	printf("/////////////////////here///////////////\n");
	return (EXIT_SUCCESS);
}
