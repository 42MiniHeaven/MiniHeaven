/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expander_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:43:39 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/06 17:00:09 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

/*
 * DESCRIPTION
 * Checks if word requires expansion.
 * 
 * Returns true if the word contains a '$' that is not inside single quotes 
 * (based on the mask), otherwise false.
 */

bool	needs_expansion_word(char *word, char *mask)
{
	int i;
	int needed;
	
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

/*
 * DESCRIPTION
 * Checks if any string in the array requires variables expansion. This 
 * function is called after the first expansion check in word.
 * 
 * Iterates throug the array and returns true if at least one element
 * contains a '$' outside of single quotes.
 */

// bool	needs_expansion_argv(char **arr)
// {
// 	int		i;
// 	int		j;
// 	char	*mask;
	
// 	i = 0;
// 	while (arr[i])
// 	{
// 		j = 0;
// 		mask = create_mask(arr[i]);
// 		if (!mask)
// 			return (free(mask), false);
// 		if (ft_strchr(arr[i], '$') != NULL)
// 		{
// 			while (arr[i][j] && mask[j])
// 			{
// 				if (arr[i][j] == '$' && mask[j] != 'S')
// 					return (free(mask), true);
// 				j++;
// 			}
// 		}
// 		free(mask);
// 		i++;
// 	}
// 	return (false);
// }

