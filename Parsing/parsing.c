/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 08:58:42 by lribette          #+#    #+#             */
/*   Updated: 2024/02/05 14:20:47 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

//int	number_of_quotes()

void	parsing(t_parsing *main, char *input)
{
	alloc_tables(main, input);
	check_commands(main);
	// prendre le cas ou check_commands renvoit exit failure
	printf("argc = %d\n", main->argc);
}
// comptabiliser les guillemets
// regarder le nombre de symboles identiques d'affilee
// regarder pour plusieurs symboles differents cote a cote
// soustraire le nombre d'espaces
// malloc les tableaux