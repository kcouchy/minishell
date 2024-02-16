/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:10:57 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/16 17:35:28 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./../Pipex/pipex.h"

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
		while(main->common.envp[i])
		{
			if (main->common.envp[i][0] != '_')
				write(STDOUT_FILENO, main->common.envp[i], ft_strlen(main->common.envp[i]));
			i++;
		}
	}
	return (EXIT_SUCCESS);
}