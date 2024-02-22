/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:06:41 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/22 13:06:13 by lribette         ###   ########.fr       */
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
				ft_fatal_parent(pipex, main); //CHECK IF IN PARENT ONLY
				//NEEDS A RETURN HERE, OR JUST STRAIGHT EXIT AS IN CHILD
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

// void	sigint_handler_hd(int signal)
// {
// 	g_signal = 2;
// 	if (signal == SIGINT)
// 	{
// 		rl_on_new_line(); //needed to reshow prompt
// 		rl_replace_line("", 1); //empties readline buffer in case there's something before the ^C
// 		write(STDIN_FILENO, "\r", 1);
// 		rl_redisplay(); //effectively forces the prompt to redisplay before you type
// 	}
// 	//set exitcode to 130 (will need a global variable to stock this)
// }

int	ft_heredoc(t_pipex *pipex, t_args **temp, int i)
{
	char	*line;
	char	*char_i;
	char	*temp_i;
	int		temp_fd;

	line = NULL;
	char_i = ft_itoa(i);
	if (!char_i)
		return (EXIT_FAILURE);
	temp_i = ft_strjoin("./heredocs/temp_", char_i);
	if (!temp_i)
		return (EXIT_FAILURE);
	if ((*temp)->input)
	{
		free((*temp)->input);
		(*temp)->input = NULL;
	}
	(*temp)->input = temp_i;
	temp_fd = open(temp_i, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (temp_fd == -1) //can trigger this open fail with permissions for leak test
		return (EXIT_FAILURE);
	while (1)
	{
		write(STDERR_FILENO, "> ", 2);
		line = gnl(STDIN_FILENO);
		if (g_signal == 2)
		{
			close(temp_fd);
			temp_fd = open(temp_i, O_RDWR | O_TRUNC | O_CREAT, 0644);
			break ;
		}
		if (!line)
		{
			ft_byedoc(pipex, *temp);
			break ;
		}
		else if (ft_strncmp(line, "\n", 1) != 0)
			if (ft_strncmp(line, (*temp)->input_files[i],
					(ft_strlen(line) - 1)) == 0)
				break ;
		write(temp_fd, line, ft_strlen(line));
		if ((*temp)->input_files[i][0] == '\0' && ft_strncmp(line, "\n", 1) == 0) // should handle limiter of "", to end the heredoc
			break;
		free(line);
	}
	g_signal = 0;
	free(line);
	free(char_i);
	close(temp_fd);
	signal(SIGINT, &sigint_handler);
	return (0);
}

void	ft_pipex_init(t_pipex *pipex, t_struct *main)
{
	pipex->temp_fd_out = -1;
	pipex->exit_code = 0;
	pipex->paths = ft_extract_paths(main->common.envp);
}

int	ft_redirections(t_pipex *pipex, t_struct *main)
{
	t_args	*temp;
	int		i;
	int		fd;

	temp = main->args_list;
	i = 0;
	fd = -1;
	while (temp)
	{
		if (temp->input_files)
		{
			i = 0;
			while (temp->input_files[i])
			{
				fd = -1;
				if (ft_strcmp(temp->input_redirs[i], "<") == 0)
				{
					fd = open(temp->input_files[i], O_RDONLY);
					if (fd == -1)
						return (EXIT_FAILURE);
					close(fd);
					if(temp->input)
					{
						free(temp->input);
						temp->input = NULL;
					}
					temp->input = ft_strdup(temp->input_files[i]);
					if(!temp->input)
						return (EXIT_FAILURE);
				}
				else if (ft_strcmp(temp->input_redirs[i], "<<") == 0)
					if (ft_heredoc(pipex, &temp, i) == 1)
						return (EXIT_FAILURE);
				i++;
			}
		}
		if (temp->output_files)
		{
			i = 0;
			while (temp->output_files[i])
			{
				fd = -1;
				if (ft_strcmp(temp->output_redirs[i], ">") == 0)
				{
					fd = open(temp->output_files[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
					temp->output_type = 0;
				}
				else if (ft_strcmp(temp->output_redirs[i], ">>") == 0)
				{
					fd = open(temp->output_files[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
					temp->output_type = 1;
				}
				if (fd == -1)
					return (EXIT_FAILURE);
				close(fd);
				i++;
			}
			if(temp->output)
			{
				free(temp->output);
				temp->output = NULL;
			}
			temp->output = ft_strdup(temp->output_files[i - 1]);
			if(!temp->output)
				return (EXIT_FAILURE);
		}
		printf("temp->output %s\n", temp->output);
		printf("temp->input %s\n", temp->input);
		temp = temp->next;
	}
	return (0);
}


int		executing(t_struct *main)
{
	t_pipex	pipex;

	ft_pipex_init(&pipex, main);
	if (ft_redirections(&pipex, main) == 1)
	{
		write(STDERR_FILENO, "finishell: open failure : redirections\n", 39);
		ft_freetable(pipex.paths);
		return (EXIT_FAILURE);
	}

	// UNLINK TEMP HEREDOC FILES
	// if (main->common.nb_commands < 1)
	// {
	// 	if (pipex.heredoc == 1)
	// 		unlink("temp");
	// 	return (0);
	// }

	ft_pipex(&pipex, main);
	g_signal = 0;
	// UNLINK TEMP HEREDOC FILES
	// if (pipex.heredoc == 1 && pipex.infile_fd != -1)
	// {
	// 	close(pipex.infile_fd);
	// 	unlink("temp");
	// }

	ft_freetable(pipex.paths);
	// ft_free_pipex(&pipex);
	// printf("---------%d--------\n", pipex.exit_code);
	return (pipex.exit_code);
}
