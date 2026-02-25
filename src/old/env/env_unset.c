/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 20:03:27 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/14 15:21:39 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../../include/miniheaven.h"

/**
 * @brief   Removes an element from the environment list.
 *
 * Compares the given key to all node keys and removes the matching node.
 *
 * @param   env	Head of linked list.
 * @param   key	Input string identifying the element to remove.
 */

void	env_unset(t_env **env, char *key)
{
	t_env	*curr;
	t_env	*prev;
	size_t	len;

	len = ft_strlen(key);
	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strncmp(curr->key, key, len) == 0 && curr->key[len] == '\0')
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
