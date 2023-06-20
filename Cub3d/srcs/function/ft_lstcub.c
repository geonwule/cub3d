/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:56:24 by geonwule          #+#    #+#             */
/*   Updated: 2023/06/14 13:22:24 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// t_map	*ft_lstnew_cub(void *content)
// {
// 	t_map	*new;

// 	new = (t_map *)ft_malloc(sizeof(t_map));
// 	new->line = ft_strdup(content);
// 	new->line_len = ft_strlen(new->line);
// 	new->next = NULL;
// 	new->prev = NULL;
// 	return (new);
// }

// t_map	*ft_lstlast_cub(t_map *lst)
// {
// 	t_map	*last;

// 	if (lst == NULL)
// 		return (0);
// 	while (lst)
// 	{
// 		last = lst;
// 		lst = lst->next;
// 	}
// 	return (last);
// }

// void	ft_lstadd_back_cub(t_map **lst, t_map *new)
// {
// 	t_map	*temp;
// 	t_map	*last;

// 	if (new == NULL)
// 		return ;
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	temp = *lst;
// 	last = ft_lstlast_cub(temp);
// 	last->next = new;
// 	new->prev = last;
// }

// int	ft_lstsize_cub(t_map *lst)
// {
// 	int	count;

// 	count = 0;
// 	while (lst)
// 	{
// 		count++;
// 		lst = lst->next;
// 	}
// 	return (count);
// }
