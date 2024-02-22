/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:34:45 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/22 13:09:55 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strljoin(char *s1, char *s2, int len)
{
	int		i;
	int		j;
	char	*output;

	i = 0;
	j = 0;
	output = malloc(ft_strlen(s1) + len + 1);
	if (!output)
		return (NULL);
	while (s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	while (len > 0)
	{
		output[i] = s2[j];
		i++;
		j++;
		len--;
	}
	output[i] = '\0';
	free(s1);
	return (output);
}

char	*ft_gnl_buff2line(char *line, char *buffer)
{
	if (ft_findnl(buffer) == -1)
	{
		line = ft_strljoin(line, buffer, ft_strlen(buffer));
		if (!line)
			return (NULL);
		buffer[0] = '\0';
	}
	else if (ft_findnl(buffer) >= 0)
	{
		line = ft_strljoin(line, buffer, ft_findnl(buffer) + 1);
		if (!line)
			return (NULL);
		buffer = ft_strcpy(buffer, buffer + ft_findnl(buffer) + 1);
	}
	return (line);
}

char	*ft_gnl_read2buff(char *line, char *buffer, int fd)
{
	int	readlen;

	while (ft_findnl(line) < 0)
	{
		readlen = read(fd, buffer, GNL_BUFFER_SIZE);
		if (readlen < 0)
			return (free(line), NULL);
		if (readlen == 0)
		{
			buffer[0] = '\0';
			break;
		}
		else
		{
			buffer[readlen] = '\0';
			line = ft_buff2line(line, buffer);
			if (!line)
				return (NULL);
		}
	}
	if (ft_strlen(line) == 0)
		return (free(line), NULL);
	return (line);
}

void	sigint_handler_gnl(int signal)
{
	g_signal = 2;
	if (signal == SIGINT)
		write(STDIN_FILENO, "\n", 1);
}

char	*gnl(int fd)
{
	static char			buffer[GNL_BUFFER_SIZE] = "";
	char				*line;
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sigint_handler_gnl;
	SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	line = malloc(sizeof(char)*1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	if (ft_strlen(buffer) > 0)
	{
		line = ft_buff2line(line, buffer);
		if (line == NULL)
			return (NULL);
	}
	if (ft_findnl(line) < 0)
	{
		line = ft_read2buff(line, buffer, fd);
		if (line == NULL)
			return (NULL);
	}
	return (line);
}
