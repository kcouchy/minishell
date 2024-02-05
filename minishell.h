/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:11:50 by lribette          #+#    #+#             */
/*   Updated: 2024/02/05 12:12:49 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./Pipex/pipex.h"

typedef enum e_type
{
	WORD = 1,
	SEPARATOR,
	COMMAND,
	OPTION,
	ARGUMENT,
	VARIABLE,
	PIPE,
	REDIRECTION,
	EQUAL
}	t_type;

typedef struct s_parsing
{
	char	**argv;
	int		*types;
	int		len;
}	t_parsing;

/******************************************************************************/
/* Parsing	                                                                  */
/******************************************************************************/

/* *************** utils.c *************** */
int		is_separator(char c);
int		is_space(char c);
int		ft_strcmp(char *s1, char *s2);

void	alloc_tables(t_parsing *main, char *input);
int		check_commands(t_parsing *main);
int		count_types(char *input);
void	parsing(t_parsing *main, char *input);

#endif