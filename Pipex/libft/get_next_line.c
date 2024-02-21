/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:19:54 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/21 18:06:06 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_buff2line(char *line, char *buffer)
{
	int	find_nl;

	find_nl = ft_findnl(buffer);
	if (find_nl >= 0)
	{
		buffer[find_nl] = '\0';
		line = ft_gnl_strjoin(line, buffer);
		if (line == NULL)
			return (NULL);
		line = ft_gnl_strjoin(line, "\n");
		if (line == NULL)
			return (NULL);
		buffer = ft_strcpy(buffer, buffer + find_nl + 1);
		return (line);
	}
	line = ft_gnl_strjoin(line, buffer);
	if (line != NULL)
		buffer[0] = '\0';
	return (line);
}

char	*ft_read2buff(char *line, char *buffer, int fd)
{
	int			read_len;

	while (ft_findnl(line) < 0)
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len == 0)
		{
			buffer[0] = '\0';
			break ;
		}
		if (read_len < 0)
			return (free(line), NULL);
		buffer[read_len] = '\0';
		if (ft_findnl(buffer) >= 0)
			return (ft_buff2line(line, buffer));
		line = ft_gnl_strjoin(line, buffer);
		if (line == NULL)
			return (NULL);
	}
	if (ft_gnl_strlen(line) == 0)
		return (free(line), NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	t_buffer[FD_MAX][BUFFER_SIZE + 1] = {0};
	char		*buffer;
	char		*line;

	buffer = t_buffer[fd];
	line = ft_gnl_calloc(1, sizeof(char));
	if (line == NULL)
		return (NULL);
	if (ft_gnl_strlen(buffer) > 0)
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

// int	main(void)
// {
// 	int		fd;
// 	int		fd1;
// 	int		count;
// 	char	*line;

// 	count = 0;
// 	fd1 = (open("read_error.txt", O_RDONLY));
// 	fd = (open("lines_around_10.txt", O_RDONLY));
// 	// printf("#%s*%s", get_next_line(fd1), get_next_line(fd));
// 	// printf("#%s*%s", get_next_line(fd1), get_next_line(fd));
// 	// printf("#%s*%s", get_next_line(fd1), get_next_line(fd));
// 	// printf("#%s*%s", get_next_line(fd1), get_next_line(fd));
// 	// printf("#%s*%s", get_next_line(fd1), get_next_line(fd));
// 	// close (fd);
// 	// close (fd1);
// 	// return(0);
// 	printf("FILE1\n");
// 	while (1)
// 	{
// 		line = get_next_line(fd1);
// 		printf("*%s*", line);
// 		free(line);
// 		if (line == NULL)
// 			break ;
// 		count++;
// 	}
// 	printf("\nNUMBER OF LINES = %d\n", count);
// 	count = 0;
// 	printf("\nFILE2\n");
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		printf("*%s*", line);
// 		free(line);
// 		if (line == NULL)
// 			break ;
// 		count++;
// 	}
// 	free(line);
// 	close (fd);
// 	printf("\nNUMBER OF LINES = %d", count);
// 	return (0);
// }
