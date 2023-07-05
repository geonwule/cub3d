/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_copy_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 00:11:15 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/05 18:20:43 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*allocate_and_copy_string(char *src)
{
	char	*dst;

	dst = (char *)ft_malloc(sizeof(char) * ft_strlen(src));
	dst[ft_strlen(src) - 1] = '\0';
	ft_memcpy(dst, src, ft_strlen(src) - 1);
	return (dst);
}
