/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 13:58:11 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/13 15:40:09 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	redir_error(t_redir *tmp)
{
	ft_error(tmp->file,": ambiguous redirect", 2);
	free(tmp->file);
	tmp->file = NULL;
}

void	ft_error(char *func, char *error, int fd)
{
	char *first;
	char *second;
	
	first = ft_strjoin("minishell: ", func);
	if (!first)
		return ;
	second = ft_strjoin(first, error);
	if (!second)
		return (free(first));
	ft_putstr_fd(second, fd);
	free(first);
	free(second);
}
