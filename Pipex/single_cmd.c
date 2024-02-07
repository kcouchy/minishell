/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:46:48 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/07 17:24:40 by kcouchma         ###   ########.fr       */
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
// 	int	out_fd;

// //SECTION 1 - infile
// 	if (pipex->heredoc == 1)
// 		pipex->infile_fd = open("/tmp/temp", O_RDONLY);
// 	else
// 		pipex->infile_fd = open(pipex->infile, O_RDONLY);
// 	if (pipex->infile_fd == -1)
// 	{
// 		perror("cannot open input file");
// 		ft_freetable(pipex->child_args);
// 		ft_freetable(pipex->paths);
// 		free(pipex->pwd_origin);
// 		exit(EXIT_FAILURE);
// 	}
// 	dup2(pipex->infile_fd, STDIN_FILENO);

// //SECTION 2 - outfile
// 	if (pipex->heredoc == 1) //will need to change this to if ">>"
// 		out_fd = open(pipex->outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
// 	else
// 		out_fd = open(pipex->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 	if (out_fd == -1)
// 	{
// 		perror("cannot open output file");
// 		ft_freetable(pipex->child_args);
// 		ft_freetable(pipex->paths);
// 		free(pipex->pwd_origin);
// 		exit(EXIT_FAILURE);
// 	}
// 	dup2(out_fd, STDOUT_FILENO);
}