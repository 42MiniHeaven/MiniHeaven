/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 14:22:26 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/22 17:22:43 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	env_remove(t_environment *list, const char *key)
{
	t_env	*curr;
	t_env	*prev;

	if (!list || !key)
		return (0);
	curr = list->head;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				list->head = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			list->size--;
			return (1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}
