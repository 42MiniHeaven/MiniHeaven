/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:11:16 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/09 17:33:14 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	env_add(t_environment *list, t_env *node)
{
	if (!list || !node)
		return (0);
	node->next = list->head;
	list->head = node;
	list->size++;
	return (1);
}
