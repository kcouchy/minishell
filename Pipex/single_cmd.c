/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:46:48 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/08 15:28:55 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
//compiled from the ft_first/last_cmd functions, can extract these sections
//to separate in/out functions to be called by both ft_first/last_cmd and single
//command functions, leaving only the pipe redirections in the 
//ft_first/last_cmd functions.

void	ft_single_cmd(t_pipex *pipex)
{
	ft_inputs(pipex);
	ft_outputs(pipex);
}