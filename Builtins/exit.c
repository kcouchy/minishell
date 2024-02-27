/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:50:23 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/27 18:44:55 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Pipex/pipex.h"

//leaks like hell, need to make sure to free everything that has been malloced
//up until this point in the program - even if you're in the middle of a pipeline

//if there is only one argument, exit exits minishell
// if it's in a pipeline, exit exits the child process, it writes nothing so the
//pipe empties out, like sleep does

// int	ft_exit(int argc, char **argv, t_pipex *pipex)
// {
// 	(void)argv;
// 	(void)pipex;
// 	if (argc > 2)
// 	{
// 		printf("finishell: exit: too many arguments");
// 		return (EXIT_FAILURE);
// 	}
// 	//this free will obviously need to be modified to handle all cases
// 	// ft_freetable(pipex->paths);
// 	//return ((int)argv[1]); //return n value
// 	return (EXIT_SUCCESS); //replace with return n value (above)
// }

void	ft_write_join(char *error_type, char *cmd, char *arg, char *str)
{
	write(STDOUT_FILENO, error_type, ft_strlen(error_type));
	write(STDOUT_FILENO, cmd, ft_strlen(cmd));
	write(STDOUT_FILENO, arg, ft_strlen(arg));
	write(STDOUT_FILENO, str, ft_strlen(str));
	write(STDOUT_FILENO, RESET, ft_strlen(RESET));
}

static int	_error(char *str)
{
	ft_write_join(ORANGE, " exit: ", str,
		": numeric argument required\n");
	return (2);
}

int	exit_atoi(char *str)
{
	int					i;
	unsigned long long	integer;
	unsigned long long	nega;

	i = 0;
	integer = 0;
	nega = 0;
	if (str[i] == '-')
	{
		nega = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		integer = integer * 10 + str[i++] - 48;
		if (integer > 9223372036854775807 + nega)
		{
			integer = _error(str);
			break ;
		}
	}
	if (str[i])
		integer = _error(str);
	return (integer % 256);
}

int	ft_exit(t_args *arg)
{
	int	exit_code;

	exit_code = 0;
	if (arg->args)
		exit_code = exit_atoi(arg->command_table[1]);
	return (exit_code);
}
