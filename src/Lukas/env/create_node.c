/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:38:18 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/06 21:27:27 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

t_env	*env_create_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env)); //TODO
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	if (node->value)
		node->flag = 1;
	else
		node->flag = 0;
	node->next = NULL;
	return (node);
}
