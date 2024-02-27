/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:27:08 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/27 15:18:36 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Pipex/pipex.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	if (tab)
		while (tab[i])
			i++;
	return (i);
}

void	builtins_parsing(t_parsing *parse)
{
	int	i;

	i = 0;
	while (parse->argv[i])
	{
		if (parse->types[i] == COMMAND && is_builtin(parse->argv[i])
			&& !ft_strcmp(parse->argv[i], "echo"))
			i = echo_parsing(parse, i + 1);
		else
			i++;
	}
}

int	builtins_executing(t_args *arg, t_struct *main)
{
	if (!ft_strcmp(arg->command_name, "echo"))
		return (ft_echo(arg));
	else if (!ft_strcmp(arg->command_name, "cd") && !arg->flags)
		return (1);
	else if (!ft_strcmp(arg->command_name, "pwd") && !arg->flags)
		return (1);
	else if (!ft_strcmp(arg->command_name, "export") && !arg->flags)
		return (ft_export(arg, main));
	else if (!ft_strcmp(arg->command_name, "unset") && !arg->flags)
		return (1);
	else if (!ft_strcmp(arg->command_name, "env") && !arg->flags && !arg->args)
		return (ft_env(main));
	else if (!ft_strcmp(arg->command_name, "exit") && !arg->flags)
		return (ft_exit(arg));
	else
	{
		arg->is_builtin = 2;
		return (EXIT_FAILURE);
	}
}

void	ft_builtin_fail(t_pipex *pipex, t_args *arg, t_struct *main)
{
	int	exit_code;

	if (arg->is_builtin == 1)
		exit_code = EXIT_SUCCESS;
	else
	{
		write(STDERR_FILENO, RED" misuse of a builtin\n"RESET, 54);
		exit_code = BUILTIN_ERROR;
	}
	ft_exit_error(pipex, main, exit_code);
}

void	ft_execve(t_pipex *pipex, t_args *arg, t_struct *main)
{
	char	*cmd_path;
	int		i;

	cmd_path = 0;
	i = 0;
	if (arg->is_builtin)
	{
		builtins_executing(arg, main);
		return ;
	}
	while (pipex->paths[i])
	{
		if (arg->command_name[0] == '.' || arg->command_name[0] == '/')
			execve(arg->command_name, arg->command_table, main->common.f_envp);
		cmd_path = ft_strjoin3(pipex->paths[i], "/", arg->command_name);
		if (!cmd_path) //replace/move this with something from errors.c -> fatal error
		{
			write(STDERR_FILENO, "pipex: malloc failed: cmd_path\n", 31);
			ft_pipex_error(pipex, main, EXIT_FAILURE);
		}
		execve(cmd_path, arg->command_table, main->common.f_envp);
		i++;
		free(cmd_path);
	}
}
