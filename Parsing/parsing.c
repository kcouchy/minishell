/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 08:58:42 by lribette          #+#    #+#             */
/*   Updated: 2024/02/15 14:56:40 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

//int	number_of_quotes()

static void	test_parsing(t_parsing *parse)
{
	int	i;

	i = 0;
	while (i < parse->argc)
	{
		printf("-----\n");
		printf("argv = %s\n", parse->argv[i]);
		if (parse->types[i] == WORD)
			printf("types = WORD\n");
		if (parse->types[i] == SEPARATOR)
			printf("types = SEPARATOR\n");
		if (parse->types[i] == COMMAND)
			printf("types = COMMAND\n");
		if (parse->types[i] == OPTION)
			printf("types = OPTION\n");
		if (parse->types[i] == ARGUMENT)
			printf("types = ARGUMENT\n");
		if (parse->types[i] == VARIABLE)
			printf("types = VARIABLE\n");
		if (parse->types[i] == PIPE)
			printf("types = PIPE\n");
		if (parse->types[i] == REDIRECTION)
			printf("types = REDIRECTION\n");
		if (parse->types[i] == INPUT_REDIR)
			printf("types = INPUT_REDIR\n");
		if (parse->types[i] == OUTPUT_REDIR)
			printf("types = OUTPUT_REDIR\n");
		if (parse->types[i] == INPUT_FILE)
			printf("types = INPUT_FILE\n");
		if (parse->types[i] == OUTPUT_FILE)
			printf("types = OUTPUT_FILE\n");
		if (parse->types[i] == EQUAL)
			printf("types = EQUAL\n");
		i++;
	}
}

int	parsing(t_struct *main, char *input)
{
	if (check_nothing(input))
		return (0);
	main->parse.number_of_commands = 1;
	main->parse.nb_of_inputs = 0;
	main->parse.nb_of_outputs = 0;
	main->parse.nb_of_flags = 0;
	main->parse.error = 0;
	alloc_tables(&main->parse, input);
	check_commands(&main->parse);
	// prendre le cas ou check_commands renvoit exit failure
	printf("argc = %d\n", main->parse.argc);
	main->common->nb_commands = main->parse.number_of_commands;
	if (!main->parse.error)
		main->args_list = parsing_to_executing(main);
	test_parsing(&main->parse);
	return (1);
}

// void	ft_pipex_init(t_pipex *pipex, int argc, char **argv, char **envp, int num_args)
// {
// 	pipex->commands = num_args;
// 	pipex->envp = envp;
// 	pipex->args = argv;
// 	pipex->infile = argv[1];
// 	pipex->infile_fd = -1;
// 	pipex->outfile = argv[argc - 1];
// 	pipex->child_args = NULL;
// 	pipex->temp_fd_out = -1;
// 	pipex->heredoc = 0;
// 	pipex->exit_code = 0;
// 	pipex->paths = ft_extract_envp(envp);
// 	pipex->pwd_origin = getcwd(NULL, 0);
// }

// comptabiliser les guillemets
// si la ligne est tres longue -> bug d'affichage avec readline qui va recommencer au debut de la ligne
// redirection sans commande
// regarde les erreurs de bash entre redirections et pipes
// faire char **command_table

// ou est input et ou est output
// stdin : file or heredoc or stdin
// stdout : append or truncate or stdout
// check ||

// regarde > test salut -> salut = argument != command

// echo -n -nnn bonjour les amis -n > test.txt | cat -e < test.txt >bonjour.txt                 >salut.txt
// echo -n bonjour -n -nn | cat -e Makefile main.c parsing.c > test.txt