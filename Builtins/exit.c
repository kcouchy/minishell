/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:50:23 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/20 16:02:22 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./../Pipex/pipex.h"

//leaks like hell, need to make sure to free everything that has been malloced
//up until this point in the program - even if you're in the middle of a pipeline

//if there is only one argument, exit exits minishell
// if it's in a pipeline, exit exits the child process, it writes nothing so the
//pipe empties out, like sleep does

int	ft_exit(int argc, char **argv, t_pipex *pipex)
{
	(void)argv;
	if (argc > 2)
	{
		printf("finishell: exit: too many arguments");
		return (EXIT_FAILURE);
	}
	//this free will obviously need to be modified to handle all cases
	ft_free_pipex(pipex);
	//return ((int)argv[1]); //return n value
	return (EXIT_SUCCESS); //replace with return n value (above)
}