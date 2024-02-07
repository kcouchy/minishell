/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 08:58:42 by lribette          #+#    #+#             */
/*   Updated: 2024/02/07 18:13:46 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

//int	number_of_quotes()

void	parsing(t_struct *main, char *input)
{
	main->parse.number_of_commands = 1;
	alloc_tables(&main->parse, input);
	check_commands(&main->parse);
	// prendre le cas ou check_commands renvoit exit failure
	printf("argc = %d\n", main->parse.argc);
	parsing_to_executing(main);
}

void	init_arg(t_args *command, t_struct *main, int start/*, int end*/)
{
	command->whole_command = NULL;
	command->command_name = strdup(main->parse.argv[start]);
	command->flags = NULL;
	command->arguments = NULL;
	command->redirection = NULL;
	command->file = NULL;
	command->is_builtin = 0;
}

t_args	*ft_structnew(t_struct *main, int start/*, int end*/)
{
	t_args	*add2list;

	add2list = malloc(sizeof(t_args));
	if (add2list)
	{
		init_arg(add2list, main, start/*, end*/);
		add2list->next = NULL;
	}
	printf("command_name = %s\n", add2list->command_name);
	return (add2list);
}

void	ft_structadd_front(t_args **commands, t_args *temp)
{
	temp->next = *commands;
	*commands = temp;
}

t_args	*parsing_to_executing(t_struct *main)
{
	t_args	*commands;
	t_args	*temp;
	int	i;
	int	start;
	int	end;

	i = 0;
	end = 0;
	commands = NULL;
	printf("number_of_commands = %d\n", main->parse.number_of_commands);
	while (i < main->parse.number_of_commands)
	{
		if (main->parse.types[end] == PIPE)
			end++;
		start = end;
		while (end < main->parse.argc && main->parse.types[end] != PIPE)
			end++;
		temp = ft_structnew(main, start/*, end*/);
		if (!temp)
			return (temp);
		ft_structadd_front(&commands, temp);
		i++;
	}
	// n'oublie pas de free la liste chainee!
	return (commands);
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