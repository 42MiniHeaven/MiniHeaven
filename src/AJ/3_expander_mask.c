/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expander_mask.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 20:07:05 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/22 17:41:35 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

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

static void	fill_mask(char c, char *quote, char *mask_char)
{
	if (*quote == 0 && (c == '"' || c == '\''))
	{
		*quote = c;
		*mask_char = 'Q';
	}
	else if (*quote != 0 && c == *quote)
	{
		*mask_char = 'Q';
		*quote = 0;
	}
	else if (*quote == '\'')
		*mask_char = 'S';
	else if (*quote == '"')
		*mask_char = 'D';
	else
		*mask_char = 'N';
}

char	*create_mask(char *str)
{
	int		i;
	char	*mask;
	char	quote;
	char	mask_char;

	if (!str)
		return (NULL);
	mask = ft_calloc((ft_strlen(str) + 1), sizeof(char));
	if (!mask)
		return (NULL);
	i = 0;
	quote = 0;
	while (str[i])
	{
		fill_mask(str[i], &quote, &mask_char);
		mask[i] = mask_char;
		i++;
	}
	return (mask);
}
