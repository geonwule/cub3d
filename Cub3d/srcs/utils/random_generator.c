/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_generator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:03:07 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/05 11:13:28 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	random_generator(int frequency)
{
	struct timeval		tv;
	unsigned long long	milliseconds;
	int					ret;

	gettimeofday(&tv, NULL);
	milliseconds = (unsigned long long)(tv.tv_usec);
	srand((unsigned int)milliseconds);
	ret = rand();
	if (ret % frequency == 0)
		return (1);
	return (0);
}
