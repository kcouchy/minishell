/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:26:27 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/02 14:52:58 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// kcouchma@c1r4p5:~$ echo "hello" $?
// hello 0
// kcouchma@c1r4p5:~$ echo "hello" | cat -e
// hello$
// kcouchma@c1r4p5:~$ echo "hello\n hello" | cat -e
// hello\n hello$
// kcouchma@c1r4p5:~$ echo 'hello\n hello' | cat -e
// hello\n hello$
// kcouchma@c1r4p5:~$ echo hello\n hello | cat -e
// hellon hello$

// To IMPLEMENT IN PARSING :
//skip \ if not within brackets

int	ft_echo(int argc, char **argv)
{
	int	i;
	int	n;

	i = 0;
	if (ft_strncmp(argv[1], "-n", 2) == 0)
		i = 1;
	n = i;
	while (i < argc)
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i++;
		if(i != argc)
			write(STDOUT_FILENO, " ", 1);
	}
	if (n == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}