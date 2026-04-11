/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_quotes_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:19:12 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/11 23:21:40 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

/*
 * QUOTE HANDLING
 * During parsing it is checked if there is a heredoc quote removal
 * necessary.
 */

//***************************** HEREDOC ****************************

int	find_heredoc_len(char *str)
{
	char	*mask;
	int		len;
	int		i;

	mask = create_mask(str);
	len = 0;
	i = 0;
	while (mask[i])
	{
		len++;
		if (mask[i] == 'Q')
			len--;
		i++;
	}
	free(mask);
	return (len);
}

char	*handle_heredoc_quotes(char *str)
{
	int		len;
	int		i;
	int		j;
	char	*result;
	char	*mask;

	if (!str)
		return (NULL);
	if (!ft_strchr(str, '\'') && !ft_strchr(str, '"'))
		return (str);
	len = find_heredoc_len(str);
	i = -1;
	j = -1;
	result = ft_calloc(len + 1, sizeof(char));
	mask = create_mask(str);
	while (str[i])
	{
		if (mask[++i] != 'Q')
			result[++j] = str[i];
	}
	free(str);
	str = result;
	free(mask);
	return (str);
}

bool	need_heredoc_expansion(char *str)
{
	int	len;

	if (!str)
		return (false);
	len = ft_strlen(str);
	if (str[0] == str[len - 1] && (str[0] == '\'' || str[0] == '"'))
		return (false);
	return (true);
}
