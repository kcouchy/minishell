/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:06:41 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/19 17:57:58 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"
#include "pipex.h"

void	ft_bonus_pipex(t_pipex *pipex, t_struct *main)
{
	int		i;
	t_args	*child_args;

	child_args = main->args_list;
	i = 0;
	// if (main->common.nb_commands == 1)
	// 	ft_single_cmd(pipex, child_args, main);
	// else
	// {
	while (child_args)
	{
		if (i < (main->common.nb_commands - 1))
		{
			if (pipe(pipex->pipe_fd) == -1)
				ft_pipe_fail(pipex);
		}
		ft_bonus_forkchild(pipex, i, child_args, main);
		if (i == 0)
			pipex->pid_last = pipex->pid;
		if (i < (main->common.nb_commands - 1))
			close(pipex->pipe_fd[0]);
		i++;
		child_args = child_args->next;
	}
	if (pipex->pid != 0)
		ft_wait_parent(pipex, main->common.nb_commands);
	// }
}

void	sigint_handler_hd(int signal)
{
	g_signal = 2;
	if (signal == SIGINT)
	{
		rl_on_new_line(); //needed to reshow prompt
		rl_replace_line("", 1); //empties readline buffer in case there's something before the ^C
		write(1, "\n", 1);
		// rl_redisplay(); //effectively forces the prompt to redisplay before you type
	}
	//set exitcode to 130 (will need a global variable to stock this)
}

void	ft_heredoc(t_pipex *pipex, t_args *args_list)
{
	char	*buffer;

	// will need to change this input_files[0] to a limiter variable once multiple redirections are done
	signal(SIGINT, &sigint_handler_hd);
	buffer = NULL;
	pipex->heredoc = 1;
	pipex->infile_fd = open("/tmp/temp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (pipex->infile_fd == -1)
	{
		write(STDERR_FILENO, "finishell: open failed: heredoc\n", 32);
		ft_open_fail(pipex);
	}
	while (1)
	{
		write(STDERR_FILENO, "> ", 2);
		buffer = get_next_line(STDIN_FILENO);
		// buffer = readline("> ");
		if (!buffer)// ctrl D
		{
			ft_byedoc(pipex, args_list);
			break ;
		}
		else if (ft_strncmp(buffer, "\n", 1) != 0)
			if (ft_strncmp(buffer, args_list->input_files[0],
					(ft_strlen(buffer) - 1)) == 0)
				break ;
		write(pipex->infile_fd, buffer, ft_strlen(buffer));
		if (args_list->input_files[0][0] == '\0' && ft_strncmp(buffer, "\n", 1) == 0) // should handle limiter of "", to end the heredoc
			break;
		if (g_signal == 2)
		{
			close(pipex->infile_fd);
			pipex->infile_fd = open("/tmp/temp", O_RDWR | O_TRUNC | O_CREAT, 0644);
			// write(STDERR_FILENO, "OK", 2);
			break ;
		}
		free(buffer);
	}
	free(buffer);
	close(pipex->infile_fd);
	// signal(SIGINT, &sigint_handler);
}

void	ft_pipex_init(t_pipex *pipex, t_struct *main)
{
	pipex->infile_fd = -1;
	pipex->temp_fd_out = -1;
	pipex->heredoc = 0;
	pipex->exit_code = 0;
	pipex->paths = ft_extract_paths(main->common.envp);
}

int		executing(t_struct *main)
{
	t_pipex	pipex;

	ft_pipex_init(&pipex, main);
	if (main->args_list->input_redirs) //will need to loop this to do as many heredocs as there are for each command (nodes on args_list)
		if (ft_strcmp(main->args_list->input_redirs[0], "<<") == 0)
			ft_heredoc(&pipex, main->args_list);
			//will have to run the heredoc on loop through the structures in args_list, amd through input_args
	if (main->common.nb_commands < 1)
	{
		if (pipex.heredoc == 1)
			unlink("temp");
		return (0);
	}
	ft_bonus_pipex(&pipex, main);
	if (pipex.heredoc == 1 && pipex.infile_fd != -1)
	{
		close(pipex.infile_fd);
		unlink("temp");
	}
	ft_freetable(pipex.paths);
	// printf("---------%d--------\n", pipex.exit_code);
	return (pipex.exit_code);
}
