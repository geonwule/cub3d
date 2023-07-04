/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_copy_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 00:11:15 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/04 04:25:10 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*allocate_and_copy_string(char *src, t_vars *vars)
{
	char	*dst;

	dst = (char *)malloc(sizeof(char) * ft_strlen(src));
	if (!dst)
	{
		print_error("dst malloc err in allocate_and_copy_string func", vars);
		exit(1);
	}
	dst[ft_strlen(src) - 1] = '\0';
	ft_memcpy(dst, src, ft_strlen(src) - 1);
	return (dst);
}
