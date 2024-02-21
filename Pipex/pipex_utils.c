/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:30:14 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/21 15:40:13 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_extract_paths(char **envp)
{
	char	**paths;
	int		i;

	paths = NULL;
	i = 0;
	if (envp)
	{
		while (envp[i])
		{
			if (ft_strncmp("PATH=", envp[i], 5) == 0)
			{
				paths = ft_split(envp[i] + 5, ':');
				if (!paths)
					(write(STDERR_FILENO, "pipex: malloc failed: paths\n", 28),
						exit(EXIT_FAILURE));
			}
			i++;
		}
	}
	if (!paths)
	{
		paths = ft_split(". ", ' ');
		if (!paths)
			(write(STDERR_FILENO, "pipex: malloc failed: paths\n", 28),
				exit(EXIT_FAILURE));
	}
	return (paths);
}

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*output;
	size_t	i;

	output = malloc((ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1));
	if (!output)
		return (NULL);
	i = 0;
	while (output && s1[i])
	{
		output[i] = ((char *)s1)[i];
		i++;
	}
	while (output && *s2)
	{
		output[i++] = *(char *)s2;
		s2++;
	}
	while (output && *s3)
	{
		output[i++] = *(char *)s3;
		s3++;
	}
	output[i] = '\0';
	return (output);
}

void	ft_execve(t_pipex *pipex, t_args *child_arg, t_struct *main)
{
	char	*cmd_path;
	int		i;

	cmd_path = 0;
	i = 0;
	while (pipex->paths[i])
	{
		if (child_arg->command_name[0] == '.' || child_arg->command_name[0] == '/')
			execve(child_arg->command_name, child_arg->command_table, main->common.envp);
		cmd_path = ft_strjoin3(pipex->paths[i], "/", child_arg->command_name);
		if (!cmd_path) //replace/move this with something from errors.c -> fatal error
		{
			write(STDERR_FILENO, "pipex: malloc failed: cmd_path\n", 31);
			ft_fatal_child(pipex, main);
		}
		execve(cmd_path, child_arg->command_table, main->common.envp);
		i++;
		free(cmd_path);
	}
}
