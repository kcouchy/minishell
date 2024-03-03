/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:13:20 by lribette          #+#    #+#             */
/*   Updated: 2024/03/03 14:14:09 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./Pipex/pipex.h"

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = EXIT_SIGINT;
		write(1, "\n", 1);
		rl_on_new_line(); //needed to reshow prompt
		rl_replace_line("", 1); //empties readline buffer in case there's something before the ^C
		rl_redisplay(); //effectively forces the prompt to redisplay before you type
	}
}

char	**finishell_env(char **envp)
{
	char	**f_envp;
	int		i;

	f_envp = NULL;
	i = 0;
	while (envp[i])
		i++;
	if (!i)
		return (NULL);
	f_envp = ft_calloc(i + 2, sizeof(char *));
	if (!f_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		f_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	f_envp[i] = ft_strdup("?=0");
	return (f_envp);
}

volatile int			g_signal;

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_struct	main;

	g_signal = 0;
	(void)argv;
	if (argc != 1)
	{
		printf("Just write \x1b[38;2;200;100;0;1m./minishell\e[0m\n");
		exit(EXIT_FAILURE);
	}
	main.common.f_envp = finishell_env(envp);
	main.common.pwd = getcwd(NULL, 0);
	while (1)
	{
		errno = 0;
		signal(SIGINT, &sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		main.exit_code = 0;
		input = readline(GREEN"finishell 🤯 > "RESET); //errno?
		if (g_signal)
		{
			main.common.f_envp = ch_exit_code(g_signal, main.common.f_envp);
			g_signal = 0;
		}
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (parsing(&main, input) == EXIT_SUCCESS)
		{
			if (!main.parse.error)
			{
				// test_liste_chainee(&main);
				ft_free_parsing(&main.parse);
				main.exit_code = executing(&main);
			}
			ft_structclear(&main.args_list);
		}
		main.common.f_envp = ch_exit_code(main.exit_code, main.common.f_envp);
	}
	rl_clear_history();
	free_table(main.common.f_envp);
	free(main.common.pwd);
	return (main.exit_code); //return 1 in case of catastrophic failure
}

//_cd_error() write -> securise ?