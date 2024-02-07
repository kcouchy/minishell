/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:11:50 by lribette          #+#    #+#             */
/*   Updated: 2024/02/06 16:00:24 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./Pipex/pipex.h"

typedef enum e_type
{
	WORD = 1,
	SEPARATOR,
	COMMAND,
	ARGUMENT,
	VARIABLE
}	t_type;

typedef struct s_parsing
{
	char	**argv;
	int		*types;
	int		len;
}	t_parsing;

void	parsing(t_parsing *main, char *input);

#endif