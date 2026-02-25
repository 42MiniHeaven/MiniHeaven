/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:33:41 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/25 19:45:42 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniheaven.h"

/*File Description: Functions to modify the shells environment.
			Used by: export, unset or $PATH for example
			Environment handling (Day 1–2)
			Internal env stored as linked list.
			Converted to envp only for execve.
			Order preserved. Ownership clear.*/

/*Function Decription:	Used to create a new node for the env linked list
			Every Node consists of key, value and next.
			If we build the node with "PWD=/home/lwittwer"
			We would get:
			KEY with PWD
			VALUE with /home/lwittwer (example) or NULL
			NEXT with NULL
			We append the node later and change this pointer
*/

t_env	*env_new(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	if (node->value || !ft_strcmp(node->key, "_"))
		node->flag = 1;
	else
		node->flag = 2;
	node->next = NULL;
	return (node);
}
