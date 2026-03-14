/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:11:16 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/14 15:09:35 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	env_add(t_environment *list, t_env *node)
{
	if (!list || !node)
		return (0);
	node->next = list->head;
	list->head = node;
	list->size++;
	return (1);
}
