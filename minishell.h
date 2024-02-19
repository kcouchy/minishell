/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:11:50 by lribette          #+#    #+#             */
/*   Updated: 2024/02/19 18:02:10 by lribette         ###   ########.fr       */
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
# include "./Pipex/libft/libft.h"

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
	int		error;
}	t_parsing;

typedef struct s_common
{
	int		nb_commands;
	char	**envp;
}	t_common;

typedef struct s_args
{
	//echo -n bonjour | cat -e Makefile > test <salut
	char			*whole_cmd; //cat -e Makefile minishell.h > test
	char			**command_table; // cat ; -e ; Makefile ; minishell.h 
	char			*command_name; //"\0" ; NULL ; cat
	char			**flags; //-e
	char			*args; //Makefile minishell.h
	char			**input_redirs; //< ; <<
	char			**input_files; //salut
	char			**output_redirs; //> ; >>
	char			**output_files; //test
	int				is_builtin; //0
	struct s_args	*next; //
}	t_args;

typedef struct s_struct
{
	t_parsing	parse;
	t_common	common;
	t_args		*args_list;
	// exit_code
}	t_struct;

/******************************************************************************/
/* Parsing	                                                                  */
/******************************************************************************/

/* ******************** utils.c ******************** */
int		is_separator(char c);
int		is_space(char c);
int		is_quote(char c);
int		ft_strcmp(char *s1, char *s2);
void	is_argument_a_command(t_parsing *parse, int i);

/* ******************** Lexing ******************** */
int		what_type(t_parsing *parse, char *input, int i, int separator);
void	alloc_tables(t_parsing *parse, char *input);
int		check_commands(t_parsing *parse);

/* ******************** Parsing ******************** */
char	*ft_argjoin(char *s1, char *s2);
void	fill_strings(t_args *cmd, t_struct *main, int start, int end);
char	**fill_type(int type, t_struct *main, int start, int end);
char	**fill_table(t_struct *main, int start, int end);
int		check_nothing(char *input);
int		parsing(t_struct *main, char *input);

/*ft_free.c*/
void	ft_free_parsing(t_parsing *parse);
void	ft_structclear(t_args **cmd);
void	free_envp(char **envp);

/* ************* Parsing to Executing ************** */
t_args	*parsing_to_executing(t_struct *main);

/*prints.c*/
void	test_parsing(t_parsing *parse);
void	test_liste_chainee(t_struct *main);

int		is_builtin(char *command);

#endif
