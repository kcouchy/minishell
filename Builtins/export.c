/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:10:57 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/27 15:11:55 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./../Pipex/pipex.h"

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

	i = -1;
	export = malloc (sizeof(char *) * ft_tablen(f_envp) + 1);
	if (!export)
		return (EXIT_FAILURE);
	while (f_envp[++i])
	{
		export[i] = ft_strdup(f_envp[i]);
		if (!export[i])
			return (ft_freetable(export), EXIT_FAILURE);
	}
	export[i] = NULL;
	_sort_export(export);
	i = -1;
	while (export[++i])
	{
		if (export[i][0] != '_')
			write(STDOUT_FILENO, export[i], ft_strlen(export[i]));
		if (export[i][0] != '_')
			write(STDOUT_FILENO, "\n", 1);
	}
	return (ft_freetable(export), EXIT_SUCCESS);
}

int ft_export(t_args *arg, t_struct *main)
{
	int		i;
	char	**f_envp;

	i = 0;
	f_envp = main->common.f_envp;
	
	if (!arg->args)
		exit(_print_export(f_envp));
	//if commmand is "export" only
	
	return (EXIT_SUCCESS);
}
