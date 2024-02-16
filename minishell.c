/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:13:20 by lribette          #+#    #+#             */
/*   Updated: 2024/02/16 11:33:33 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./Pipex/pipex.h"

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line(); //needed to reshow prompt
		rl_replace_line("", 1); //empties readline buffer in case there's something before the ^C
		rl_redisplay(); //effectively forces the prompt to redisplay before you type
	}
	//set exitcode to 130 (will need a global variable to stock this)
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
	f_envp = ft_calloc(i + 1, sizeof(char *));
	if (!f_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		f_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	return (f_envp);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_struct	main;

	(void)argv;
	if (argc != 1)
	{
		printf("Just write \x1b[38;2;200;100;0;1m./minishell\e[0m\n");
		exit(EXIT_FAILURE);
	}
	//use sigaction
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	main.common.envp = finishell_env(envp);
	while (1)
	{
		input = readline(GREEN"finishell \e[5m🤯"RESET GREEN"> "RESET);
		if (!input)
			break ;
		if (parsing(&main, input))
		{
			if (!main.parse.error)
			{
				test_liste_chainee(&main);
				ft_free_parsing(&main.parse);
			}
			executing(&main);
			ft_structclear(&main.args_list);
		}
	}
	free_envp(main.common.envp);
	return (0);
}
