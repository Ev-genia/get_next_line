/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:41:29 by mlarra            #+#    #+#             */
/*   Updated: 2022/09/28 00:34:42 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_ret_line(ssize_t nbytes, char *line)
{
	if (!nbytes && line[nbytes] == '\0')
	{
		free(line);
		return (0);
	}
	return (line);
}

static char	*ft_read_line(char *line, char **tail, int fd)
{
	char	buff[BUFFER_SIZE + 1];
	ssize_t	nbytes;
	char	*tmp;

	nbytes = 1;
	while (nbytes)
	{
		nbytes = read(fd, buff, BUFFER_SIZE);
		if (nbytes < 0)
		{
			free (line);
			return ((void *)0);
		}
		buff[nbytes] = '\0';
		line = ft_strjoin(line, buff);
		if (ft_strchr(line, '\n'))
		{
			*tail = ft_strdup(ft_strchr(line, '\n') + 1);
			tmp = line;
			line = ft_substr(line, 0, ft_strlen(line) - ft_strlen(*tail));
			free(tmp);
			return (ft_ret_line(nbytes, line));
		}
	}
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*dest;
	static char	*tail[1025];

	if (fd < 0 || BUFFER_SIZE < 1 || fd > 1025)
		return ((void *)0);
	if (!tail[fd])
		tail[fd] = ft_strdup("");
	line = ft_strdup(tail[fd]);
	free(tail[fd]);
	tail[fd] = NULL;
	line = ft_read_line(line, &tail[fd], fd);
	return (line);
}
