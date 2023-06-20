/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:36:50 by geonwule          #+#    #+#             */
/*   Updated: 2023/06/01 16:13:18 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup_gnl(const char *s1, char *back)
{
	char	*s2;
	int		i;

	i = 0;
	if (s1 == NULL)
	{
		free(back);
		return (0);
	}
	s2 = (char *)ft_malloc(sizeof(const char) * ft_strlen(s1) + 1);
	while (s1[i] != 0)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	free(back);
	return (s2);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	char	d;
	int		i;

	d = c;
	i = 0;
	if (s == NULL)
		return (0);
	if (d == '\0')
	{
		while (s[i] != '\0')
			i++;
		return ((char *)&s[i]);
	}
	while (s[i] != '\0')
	{
		if (s[i] == d)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen_gnl(src);
	i = 0;
	if (dstsize == 0 || src_len == 0)
		return (src_len);
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*str;
	int		s1_len;
	int		s2_len;
	int		i[2];

	s1_len = ft_strlen_gnl(s1);
	s2_len = ft_strlen_gnl(s2);
	str = (char *)ft_malloc(sizeof(char) * (s1_len + s2_len + 1));
	i[0] = -1;
	i[1] = -1;
	while (++i[0] < s1_len)
		str[i[0]] = s1[i[0]];
	while (++i[1] < s2_len)
		str[i[0] + i[1]] = s2[i[1]];
	str[s1_len + s2_len] = '\0';
	if (s1 != NULL)
		free((void *)s1);
	return (str);
}
