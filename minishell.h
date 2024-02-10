/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:11:50 by lribette          #+#    #+#             */
/*   Updated: 2024/02/10 10:44:46 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED "\x1b[38;2;255;0;0;1mfinishell 🤬:"
# define GREEN "\x1b[38;2;0;150;0;1m"
# define RESET "\e[0m"

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
	INPUT_REDIR,
	OUTPUT_REDIR,
	INPUT_FILE,
	OUTPUT_FILE,
	EQUAL
}	t_type;

typedef struct s_parsing
{
	int		argc;
	char	**argv;
	int		*types;
	int		number_of_commands;
	int		nb_of_inputs;
	int		nb_of_outputs;
	int		nb_of_flags;
	int		error;
}	t_parsing;

typedef struct s_common
{
	void	*first_command; //
	char	**envp; //
}	t_common;

typedef struct s_args
{
	char	*whole_cmd; //
	char	*command_name; //
	char	**flags; //
	char	*args; //
	char	**input_redirs; //
	char	**input_files; //
	char	**output_redirs; //
	char	**output_files; //
	int		is_builtin; //
	struct s_args	*next; //
}	t_args;

typedef struct s_struct
{
	t_parsing	parse;
	t_common	common;
	t_args		args;
}	t_struct;

/******************************************************************************/
/* Parsing	                                                                  */
/******************************************************************************/

/* ******************** utils.c ******************** */
int		is_separator(char c);
int		is_space(char c);
int		check_nothing(char *input);
int		ft_strcmp(char *s1, char *s2);
int		is_builtin(char *command);

/* ******************** Parsing ******************** */
void	alloc_tables(t_parsing *parse, char *input);
int		check_commands(t_parsing *parse);
int		count_types(char *input);
int		parsing(t_struct *main, char *input);
void	ft_free_parsing(t_parsing *parse);

/* ************* Parsing to Executing ************** */
t_args	*parsing_to_executing(t_struct *main);

#endif
