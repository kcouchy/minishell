/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:33:22 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/16 17:35:07 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./../Pipex/pipex.h"

// chdir apparently handles relative and absolute paths and ".."

int ft_cd(t_struct *main)
{
	if (ft_tablen(main->args_list->command_table) > 2)
	{
		printf("finishell: cd: too many arguments");
		return (EXIT_FAILURE);
	}
	if (chdir(main->args_list->command_table[0]) == -1)
	{
		printf("finishell: cd: chdir failure");
		return (EXIT_FAILURE);
	}
	//UPDATE $PWD in main->common.envp with export
	return (EXIT_SUCCESS);
}
