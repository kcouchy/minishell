/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:38:49 by lribette          #+#    #+#             */
/*   Updated: 2024/03/01 14:12:27 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Pipex/pipex.h"

static int	_is_there_an_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static void	unset_arg(int i, t_struct *main)
{
	if (i == -1)
		return ;
	free(main->common.f_envp[i]);
	while (i < ft_tablen(main->common.f_envp))
	{
		main->common.f_envp[i] = main->common.f_envp[i + 1];
		i++;
	}
	main->common.f_envp[i] = NULL;
}

int	ft_unset(t_args *arg, t_struct *main)
{
	int	i;
	int	j;
	int	error;

	error = 0;
	j = 1;
	while (j < ft_tablen(arg->command_table))
	{
		if (_is_there_an_equal(arg->command_table[j]))
		{
			error = 1;
			ft_write_join(RED, " unset: `", arg->command_table[j],
				"' not a valid identifier");
		}
		else
		{
			i = find_arg(arg->command_table[j], main->common.f_envp);
			unset_arg(i, main);
		}
		j++;
	}
	return (error);
}
