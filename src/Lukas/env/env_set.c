/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:14:39 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/14 15:12:07 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniheaven.h"

int	env_set(t_environment *list, t_env *node)
{
	t_env	*curr;

	curr = list->head;
	while (curr)
	{
		if (ft_strcmp(curr->key, node->key) == 0)
		{
			free(curr->value);
			curr->value = node->value;
			curr->flag = node->flag;
			free(node->key);
			free(node);
			return (1);
		}
		curr = curr->next;
	}
	return (env_add(list, node));
}
