/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expander_mask.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 20:07:05 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/28 16:36:33 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

/*
 * DESCRIPTION
 * Creates a mask for the strings used during expansion. Each character is
 * labelled as quoted or unquoted so the expander can apply the correct rules.
 * 
 * RETURN VALUE
 * @return mask:	Newly allocated string (mask) where each position 
 * 					corresponds	to a charater in the input string.
 * 					'Q' = quote character to be removed
 * 					'D' = inside double quotes
 * 					'S' = inside single quotes
 * 					'N' = outside of quotes
 * @return NULL:	If memory allocation fails.
 */

static void	fill_mask(char *str, char *mask, int *i, char c, char type)
{
	mask[(*i)++] = 'Q';
	while (str[*i] && str[*i] != c)
		mask[(*i)++] = type;
	if (str[*i])
		mask[(*i)++] = 'Q';
}

char	*create_mask(char *str)
{
	int	i;
	char	*mask;

	mask = ft_calloc((strlen(str) + 1), sizeof(char));
	if (!mask)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			fill_mask(str, mask, &i, '"', 'D');
		else if (str[i] == '\'')
			fill_mask(str, mask, &i, '\'', 'S');
		else
			mask[i++] = 'N';
	}
	return (mask);	
}

