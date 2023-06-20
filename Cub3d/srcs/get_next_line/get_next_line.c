/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:44:44 by geonwule          #+#    #+#             */
/*   Updated: 2023/06/01 12:58:42 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*read_txt(char *back, char **n_ptr, int readsize, int fd)
{
	char		*buf;

	buf = (char *)ft_malloc(sizeof(char) * (BUFFER_SIZE + 1));
	*n_ptr = ft_strchr_gnl(back, '\n');
	while ((*n_ptr == NULL) && (readsize != 0))
	{
		readsize = read(fd, buf, BUFFER_SIZE);
		if (readsize == -1)
		{
			if (back)
				free(back);
			free(buf);
			return (0);
		}
		if (readsize == 0)
			break ;
		buf[readsize] = '\0';
		back = ft_strjoin_gnl(back, buf);
		*n_ptr = ft_strchr_gnl(back, '\n');
	}
	free(buf);
	return (back);
}

static char	*line_set(char *back)
{
	char	*line;
	int		i;

	i = 0;
	if (back[i] == '\0')
		return (0);
	while (back[i] != '\0')
	{
		if (back[i] == '\n')
			break ;
		i++;
	}
	line = (char *)ft_malloc(sizeof(char) * (i + 2));
	ft_strlcpy_gnl(line, back, i + 2);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*back;
	char		*n_ptr;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	back = read_txt(back, &n_ptr, -1, fd);
	if (back == NULL)
		return (0);
	line = line_set(back);
	if (n_ptr != NULL)
		back = ft_strdup_gnl(n_ptr + 1, back);
	else
	{
		free(back);
		back = 0;
	}
	return (line);
}
