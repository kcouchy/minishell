/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:27:08 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/23 16:28:13 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./../Pipex/pipex.h"

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

int	builtins_executing(t_args *arg)
{
	if (!ft_strcmp(arg->command_name, "echo"))
		return (ft_echo(arg));
	if (!ft_strcmp(arg->command_name, "cd") && !arg->flags)
		return (1);
	if (!ft_strcmp(arg->command_name, "pwd") && !arg->flags)
		return (1);
	if (!ft_strcmp(arg->command_name, "export") && !arg->flags)
		return (1);
	if (!ft_strcmp(arg->command_name, "unset") && !arg->flags)
		return (1);
	if (!ft_strcmp(arg->command_name, "env") && !arg->flags && !arg->args)
		return (1);
	if (!ft_strcmp(arg->command_name, "exit") && !arg->flags)
		return (1);
	else
		return (EXIT_FAILURE);
}

void	ft_execve(t_pipex *pipex, t_args *child_arg, t_struct *main)
{
	char	*cmd_path;
	int		i;

	cmd_path = 0;
	i = 0;
	if (is_builtin(child_arg->command_name))
	{
		builtins_executing(child_arg);
		return ;
	}
	while (pipex->paths[i])
	{
		if (child_arg->command_name[0] == '.' || child_arg->command_name[0] == '/')
			execve(child_arg->command_name, child_arg->command_table, main->common.f_envp);
		cmd_path = ft_strjoin3(pipex->paths[i], "/", child_arg->command_name);
		if (!cmd_path) //replace/move this with something from errors.c -> fatal error
		{
			write(STDERR_FILENO, "pipex: malloc failed: cmd_path\n", 31);
			ft_pipex_error(pipex, main, EXIT_FAILURE);
		}
		execve(cmd_path, child_arg->command_table, main->common.f_envp);
		i++;
		free(cmd_path);
	}
}
