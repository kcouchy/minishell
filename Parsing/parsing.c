/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 08:58:42 by lribette          #+#    #+#             */
/*   Updated: 2024/02/08 20:09:19 by lribette         ###   ########.fr       */
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
		if (parse->types[i] == 1)
			printf("types = WORD\n");
		if (parse->types[i] == 2)
			printf("types = SEPARATOR\n");
		if (parse->types[i] == 3)
			printf("types = COMMAND\n");
		if (parse->types[i] == 4)
			printf("types = OPTION\n");
		if (parse->types[i] == 5)
			printf("types = ARGUMENT\n");
		if (parse->types[i] == 6)
			printf("types = VARIABLE\n");
		if (parse->types[i] == 7)
			printf("types = PIPE\n");
		if (parse->types[i] == 8)
			printf("types = REDIRECTION\n");
		if (parse->types[i] == 9)
			printf("types = R_FILE\n");
		if (parse->types[i] == 10)
			printf("types = EQUAL\n");
		i++;
	}
}

int	parsing(t_struct *main, char *input)
{
	if (input[0] == '\0')
		return (0);
	main->parse.number_of_commands = 1;
	main->parse.nb_of_redir = 0;
	main->parse.nb_of_flags = 0;
	alloc_tables(&main->parse, input);
	check_commands(&main->parse);
	// prendre le cas ou check_commands renvoit exit failure
	printf("argc = %d\n", main->parse.argc);
	parsing_to_executing(main);
	test_parsing(&main->parse);
	return (1);
}

int	is_builtin(char *command)
{
	if (!ft_strcmp(command, "echo"))
		return (1);
	if (!ft_strcmp(command, "cd"))
		return (1);
	if (!ft_strcmp(command, "pwd"))
		return (1);
	if (!ft_strcmp(command, "export"))
		return (1);
	if (!ft_strcmp(command, "unset"))
		return (1);
	if (!ft_strcmp(command, "env"))
		return (1);
	if (!ft_strcmp(command, "exit"))
		return (1);
	return (0);
}

char	*ft_argjoin(char *s1, char *s2)
{
	char	*output;
	int	i;

	output = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 2), sizeof(char));
	if (!output)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		output[i] = *s2;
		i++;
		s2++;
	}
	output[i] = ' ';
	output[i + 1] = '\0';
	if (s1[0])
		free(s1);
	return (output);
}

char	*remove_space(char *str)
{
	int		i;
	int		len;
	char	*s;
	
	i = 0;
	len = ft_strlen(str) - 1;
	s = ft_calloc(len + 1, sizeof(char));
	while (i < len)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	free(str);
	return (s);
}

void	fill_strings(t_args *cmd, t_struct *main, int start, int end)
{
	int	number_of_args;

	number_of_args = 0;
	cmd->whole_cmd = "";
	cmd->args = "";
	while (start != end)
	{
		cmd->whole_cmd = ft_argjoin(cmd->whole_cmd, main->parse.argv[start]);
		if (main->parse.types[start] == ARGUMENT)
		{
			cmd->args = ft_argjoin(cmd->args, main->parse.argv[start]);
			number_of_args++;
		}
		start++;
	}
	if (cmd->whole_cmd[0])
		cmd->whole_cmd = remove_space(cmd->whole_cmd);
	if (number_of_args)
		cmd->args = remove_space(cmd->args);
}

int	count_type(int type, t_struct *main, int start, int end)
{
	int	counter;

	counter = 0;
	while (start != end)
	{
		if (main->parse.types[start] == type)
			counter++;
		start++;
	}
	return (counter);
}

char	**fill_type(int type, t_struct *main, int start, int end)
{
	char	**tab;
	int		nb_of_this_type;
	int		i;

	nb_of_this_type = count_type(type, main, start, end);
	tab = ft_calloc((nb_of_this_type) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (start != end)
	{
		if (main->parse.types[start] == type)
		{
			tab[i] = ft_strdup(main->parse.argv[start]);
			i++;
		}
		start++;
	}
	tab[i] = NULL;
	return (tab);
}

void	init_arg(t_args *cmd, t_struct *main, int start, int end)
{
	cmd->command_name = "";
	if (main->parse.argv[start])
		cmd->command_name = ft_strdup(main->parse.argv[start]);
	cmd->flags = fill_type(OPTION, main, start, end);
	cmd->redir = fill_type(REDIRECTION, main, start, end);
	cmd->file = fill_type(R_FILE, main, start, end);
	fill_strings(cmd, main, start, end);
	if (!cmd->flags || !cmd->redir || !cmd->file)
		return ;
	cmd->is_builtin = is_builtin(cmd->command_name);
	//int		nb_of_inputs;
	//int		nb_of_outputs;
}

t_args	*ft_structnew(t_struct *main, int start, int end)
{
	t_args	*add2list;

	add2list = malloc(sizeof(t_args));
	if (add2list)
	{
		init_arg(add2list, main, start, end);
		add2list->next = NULL;
	}
	printf("-----\n");
	printf("\x1b[38;2;255;0;0mwhole_cmd = %s\n", add2list->whole_cmd);
	printf("\x1b[38;2;255;132;0mcommand_name = %s\n", add2list->command_name);
	int	i = 0;
	printf("\x1b[38;2;255;216;0mflags = \n");
	while (add2list->flags[i])
	{
		printf(" -   %s\n", add2list->flags[i]);
		i++;
	}
	i = 0;
	printf("\x1b[38;2;0;255;60mredirections = \n");
	while (add2list->redir[i])
	{
		printf(" -   %s\n", add2list->redir[i]);
		i++;
	}
	i = 0;
	printf("\x1b[38;2;0;144;255mfile = \n");
	while (add2list->file[i])
	{
		printf(" -   %s\n", add2list->file[i]);
		i++;
	}
	printf("\x1b[38;2;130;25;255marguments = %s\n", add2list->args);
	printf("\x1b[38;2;255;0;0mis_builtin = %d\n", add2list->is_builtin);
	return (add2list);
}

void	ft_structadd_front(t_args **commands, t_args *temp)
{
	temp->next = *commands;
	*commands = temp;
}

t_args	*parsing_to_executing(t_struct *main)
{
	t_args	*cmd;
	t_args	*temp;
	int	i;
	int	start;
	int	end;

	i = 0;
	end = 0;
	cmd = NULL;
	printf("number_of_commands = %d\n", main->parse.number_of_commands);
	while (i < main->parse.number_of_commands)
	{
		if (main->parse.types[end] == PIPE)
			end++;
		start = end;
		while (end < main->parse.argc && main->parse.types[end] != PIPE)
			end++;
		temp = ft_structnew(main, start, end);
		if (!temp)
			return (temp);
		ft_structadd_front(&cmd, temp);
		i++;
	}
	// n'oublie pas de free la liste chainee!
	return (cmd);
}
// comptabiliser les guillemets
// regarder le nombre de symboles identiques d'affilee
// regarder pour plusieurs symboles differents cote a cote
// soustraire le nombre d'espaces
// malloc les tableaux
// regarder quand il y a juste une redirection a la fin (attention heredoc !)
// gestion d'erreurs pour le parsing par exemple | au debut
// si la ligne est tres longue -> bug d'affichage avec readline qui va recommencer au debut de la ligne
// redirection sans commande

// ou est input et ou est output
// stdin : file or heredoc or stdin
// stdout : append or truncate or stdout

// echo -n -nnn bonjour les amis -n > test.txt | cat -e < test.txt >bonjour.txt                 >salut.txt
// echo -n bonjour -n -nn | cat -e Makefile main.c parsing.c > test.txt