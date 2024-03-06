/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:37:25 by kcouchma          #+#    #+#             */
/*   Updated: 2024/03/06 14:25:44 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_command_fail(t_pipex *pipex, t_args *arg, t_struct *main)
{
	if (!arg->command_name)
		ft_write_join(RED, " command not found:", "", " ''");
	else
		ft_write_join(RED, " command not found: ", arg->command_name, "");
	ft_exit_error(pipex, main, FILENOTFOUND);
}

int	ft_byedoc(t_pipex *pipex, t_args *arg, int exit_code)
{
	ft_write_join(ORANGE, " warning: here-doc wanted `",
		arg->input_files[0], "'");
	pipex->exit_code = exit_code;
	if (errno == MALLOC_ERROR)
		return (errno);
	return (exit_code);
}

int	ft_pipex_error(t_pipex *pipex, t_struct *main, int exit_code)
{
	free_table(pipex->paths);
	if (pipex->pid == 0)
	{
		ft_structclear(&main->args_list);
		free_table(main->common.f_envp);
		free(main->common.pwd);
		if (errno == MALLOC_ERROR)
			exit (errno);
		exit(exit_code);
	}
	unlink_hds();
	if (errno == MALLOC_ERROR)
		return (errno);
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
		filename = ft_strjoinf("./Pipex/temp_", string_i, 2);
		if (errno == MALLOC_ERROR)
			return (errno);
		unlink(filename);
		free(filename);
		i++;
	}
	return (EXIT_SUCCESS);
}
