/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:50:23 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/02 18:01:50 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//leaks like hell, need to make sure to free everything that has been malloced
//up until this point in the program - even if you're in the middle of a pipeline

//if there is only one argument, exit exits minishell
// if it's in a pipeline, exit exits the child process, it writes nothing so the
//pipe empties out, like sleep does