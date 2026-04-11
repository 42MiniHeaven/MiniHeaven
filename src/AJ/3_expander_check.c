/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expander_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:43:39 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/11 23:45:13 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

/*
 * DESCRIPTION
 * Checks if word requires expansion.
 * 
 * Returns true if the word contains a '$' that is not inside single quotes 
 * (based on the mask), otherwise false.
 */

bool	needs_expansion_word(char *word, char *mask)
{
	int	i;
	int	needed;

	i = 0;
	needed = 0;
	if (ft_strchr(word, '$') != NULL)
	{
		while (word[i] && mask[i])
		{
			if (word[i] == '$' && mask[i] != 'S')
				needed = 1;
			i++;
		}
	}
	return (needed);
}
