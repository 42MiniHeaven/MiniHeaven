/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 13:58:11 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/17 18:43:16 by azielnic         ###   ########.fr       */
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
