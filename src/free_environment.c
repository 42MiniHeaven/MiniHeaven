/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:36:29 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/14 18:03:53 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniheaven.h"

void	free_environment(t_environment *list)
{
	t_env	*curr;
	t_env	*tmp;

	if (!list)
		return ;
	curr = list->head;
	while (curr)
	{
		tmp = curr->next;
		if (curr->key)
			free(curr->key);
		if (curr->value)
			free(curr->value);
		free(curr);
		curr = tmp;
	}
	list->head = NULL;
	list->size = 0;
	free(list);
	list = NULL;
}
