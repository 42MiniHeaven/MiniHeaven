/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_quotes_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:19:12 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/06 19:25:30 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

/*
 * QUOTE HANDLING
 * During parsing it is checked if there is a heredoc quote removal
 * necessary.
 */

//***************************** HEREDOC ****************************

char	*remove_quote(char *str)
{
	int		len;
	char	*ret;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if ((str[0] == str[len - 1]) && (str[0] == '"' || str[0] == '\''))
	{
		ret = ft_substr(str, 1, len - 2);
		free(str);
		return (ret);
	}
	else
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
