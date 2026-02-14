/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:19:05 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/14 15:54:41 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"
#include "../../include/execute.h"

/*General Description:	Freeing the allocated space from environment*/

/*Func Description:	Freeing the allocated space for our Array of Strings.
			frees the strings and set the arr to NULL*/

void	free_arr(char **arr)
{
	size_t	i;

	if (!arr || !*arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	arr = NULL;
}

/*Func Description:	Freeing the allocated string
			frees the string.*/

void	free_str(char *str)
{
	if (!str)
		return ;
	free(str);
	str = NULL;
}

/*Func Description:	Freeing the used linked list of our costum environment
			Mabye some rework for later*/

void	free_linked(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
