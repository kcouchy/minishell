/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:06:41 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/22 17:49:18 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"
#include "pipex.h"

void	ft_pipex(t_pipex *pipex, t_struct *main)
{
	int		i;
	t_args	*child_args;

	child_args = main->args_list;
	i = 0;
	while (child_args)
	{
		if (i < (main->common.nb_commands - 1))
		{
			if (pipe(pipex->pipe_fd) == -1)
			{
				write(STDERR_FILENO, "finishell: pipe failed\n", 23);
				ft_pipex_error(pipex, main, EXIT_FAILURE);
			}
		}
		ft_forkchild(pipex, i, child_args, main);
		if (i == 0)
			pipex->pid_last = pipex->pid;
		if (i < (main->common.nb_commands - 1))
			close(pipex->pipe_fd[0]);
		i++;
		child_args = child_args->next;
	}
	if (pipex->pid != 0)
		ft_wait_parent(pipex, main->common.nb_commands);
}

// int	ft_heredoc(t_pipex *pipex, t_args **temp, int i)
// {
// 	char	*line;
// 	char	*char_i;
// 	char	*temp_i;
// 	int		temp_fd;

// 	line = NULL;
// 	char_i = ft_itoa(i);
// 	if (!char_i)
// 		return (EXIT_FAILURE);
// 	temp_i = ft_strjoin("./Pipex/temp_", char_i);
// 	if (!temp_i)
// 		return (EXIT_FAILURE);
// 	if ((*temp)->input)
// 	{
// 		free((*temp)->input);
// 		(*temp)->input = NULL;
// 	}
// 	(*temp)->input = temp_i;
// 	temp_fd = open(temp_i, O_RDWR | O_TRUNC | O_CREAT, 0644);
// 	if (temp_fd == -1) //can trigger this open fail with permissions for leak test
// 		return (EXIT_FAILURE);
// 	while (1)
// 	{
// 		write(STDERR_FILENO, "> ", 2);
// 		line = gnl(STDIN_FILENO);
// 		if (g_signal == 2)
// 		{
// 			close(temp_fd);
// 			temp_fd = open(temp_i, O_RDWR | O_TRUNC | O_CREAT, 0644);
// 			break ;
// 		}
// 		if (!line)
// 		{
// 			ft_byedoc(pipex, *temp);
// 			break ;
// 		}
// 		else if (ft_strncmp(line, "\n", 1) != 0)
// 			if (ft_strncmp(line, (*temp)->input_files[i],
// 					(ft_strlen(line) - 1)) == 0)
// 				break ;
// 		write(temp_fd, line, ft_strlen(line));
// 		if ((*temp)->input_files[i][0] == '\0' && ft_strncmp(line, "\n", 1) == 0) // should handle limiter of "", to end the heredoc
// 			break;
// 		free(line);
// 	}
// 	g_signal = 0;
// 	free(line);
// 	free(char_i);
// 	close(temp_fd);
// 	signal(SIGINT, &sigint_handler);
// 	return (0);
// }

int	ft_pipex_init(t_pipex *pipex, t_struct *main)
{
	pipex->temp_fd_out = -1;
	pipex->pid = -1;
	pipex->exit_code = 0;
	pipex->paths = ft_extract_paths(main->common.envp);
	if (!pipex->paths)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		executing(t_struct *main)
{
	t_pipex	pipex;

	if (ft_pipex_init(&pipex, main) == EXIT_FAILURE)
	{
		write(STDERR_FILENO, "finishell: executing failure : init\n", 36);
		return (EXIT_FAILURE);
	}
	if (ft_redirections(&pipex, main) == EXIT_FAILURE)
	{
		write(STDERR_FILENO, "finishell: open failure : redirections\n", 39);
		return (ft_pipex_error(&pipex, main, EXIT_FAILURE));
	}
	if (main->common.nb_commands < 1)
		return (ft_pipex_error(&pipex, main, EXIT_SUCCESS));
	ft_pipex(&pipex, main);
	ft_pipex_error(&pipex, main, EXIT_SUCCESS);
	return (pipex.exit_code);
}
