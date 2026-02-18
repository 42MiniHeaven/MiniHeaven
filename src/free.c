/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:19:05 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/18 23:36:36 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

void	free_arr(char **arr)
{
	size_t	i;

	if (!arr || !*arr)
		return ;
	i = -1;
	while (arr[++i])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
}

void	free_str(char *str)
{
	if (!str)
		return ;
	free(str);
	str = NULL;
}

/* 
 * DESCRIPTION
 *		Freeing the used linked list of our custom environment.
 *		Maybe some rework for later.
 */
 
void	free_env(t_env *head)
{
	t_env	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->key)
		{
			free(tmp->key);
			tmp->key = NULL;
		}
		if (tmp->value)
		{
			free(tmp->value);
			tmp->value = NULL;
		}
		tmp->is_exported = 0;
		free(tmp);
	}
	tmp = NULL;
}
