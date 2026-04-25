/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 13:58:11 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/25 20:58:14 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	syntax_error(char *type)
{
	char	*msg_part;
	char	*msg_final;

	ft_putstr_fd("minishell: ", 2);
	msg_part = ft_strjoin("syntax error near unexpected token `", type);
	msg_final = ft_strjoin(msg_part, "'");
	ft_putendl_fd(msg_final, 2);
	free(msg_part);
	free(msg_final);
	return (-1);
}

void	redir_error(t_redir *tmp)
{
	ft_error(tmp->file, ": ambiguous redirect", 2);
	free(tmp->file);
	tmp->file = NULL;
}

void	ft_error(char *func, char *error, int fd)
{
	char	*first;
	char	*second;

	first = ft_strjoin("minishell: ", func);
	if (!first)
		return ;
	second = ft_strjoin(first, error);
	if (!second)
		return (free(first));
	ft_putendl_fd(second, fd);
	free(first);
	free(second);
}

static char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*joined;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	joined = ft_calloc(len1 + len2 + len3 + 1, sizeof(char));
	if (!joined)
		return (NULL);
	ft_memcpy(joined, s1, len1);
	ft_memcpy(joined + len1, s2, len2);
	ft_memcpy(joined + len1 + len2, s3, len3);
	joined[len1 + len2 + len3] = '\0';
	return (joined);
}

void	ft_err_three(char *func, char *error, char *extra)
{
	char	*first;
	char	*second;
	char	*third;

	first = ft_strjoin("minishell: ", func);
	if (!first)
		return ;
	second = ft_strjoin(first, error);
	if (!second)
		return (free(first));
	third = ft_strjoin_three(second, ": ", extra);
	if (!third)
		return (free(first), free(second));
	ft_putendl_fd(third, 2);
	free(first);
	free(second);
	free(third);
}
