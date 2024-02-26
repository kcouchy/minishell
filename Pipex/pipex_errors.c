/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:37:25 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/26 15:34:19 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_freetable(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}

void	ft_command_fail(t_pipex *pipex, t_args *arg, t_struct *main)
{
	char	*msg;

	if (!arg->command_name)
		write(STDERR_FILENO, "finishell: command not found: ''\n", 33);
	else
	{
		msg = ft_strjoin3(
				"\x1b[38;2;255;0;0;1mfinishell 🤬: command not found: ",
				arg->command_name, "\e[0m\n");
		if (!msg)//may need to set malloc error here
			write(STDERR_FILENO, "finishell: command not found\n", 29);
		else
		{
			write(STDERR_FILENO, msg, ft_strlen(msg));
			free(msg);
		}
	}
	ft_freetable(pipex->paths);
	ft_structclear(&main->args_list);
	free_envp(main->common.f_envp);
	exit(FILENOTFOUND);
}

//ctrl D (EXIT_SUCESS) exit code only
int	ft_byedoc(t_pipex *pipex, t_args *arg, int exit_code)
{
	char	*msg;

	g_signal = 0;
	pipex->exit_code = exit_code;
	msg = ft_strjoin3
		("\x1b[38;2;255;100;0;1mfinishell 🤬: warning: here-doc wanted `",
			arg->input_files[0], "'\n\e[0m");
	if (!msg)//may need to set malloc error here
		return(exit_code); //Need to change to fatal error?
	write(STDERR_FILENO, msg, ft_strlen(msg));
	free(msg);
	return (exit_code);
}

int	ft_pipex_error(t_pipex *pipex, t_struct *main, int exit_code)
{
	ft_freetable(pipex->paths);
	if (pipex->pid == 0)
	{
		ft_structclear(&main->args_list);
		free_envp(main->common.f_envp);
		exit(exit_code);
	}
	if (unlink_hds() == EXIT_FAILURE)
		write(STDERR_FILENO, RED"here-doc closure error\n"RESET, 57);
	return (exit_code);
}

int	unlink_hds(void)
{
	int		i;
	char	*filename;
	char	*string_i;

	i = 0;
	filename = NULL;
	string_i = NULL;
	while (i < 1024)
	{
		string_i = ft_itoa(i);
		if (!string_i)
			return (EXIT_FAILURE);
		filename = ft_strjoin("./Pipex/temp_", string_i);
		free(string_i);
		unlink(filename);
		free(filename);
		i++;
	}
	return (0);
}
