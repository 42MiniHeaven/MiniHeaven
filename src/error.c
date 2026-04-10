/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 13:58:11 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/11 00:21:23 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	ft_error(char *func, char *error, int fd)
{
	char *msh;
	char *first;
	char *second;
	
	msh = ft_strdup("minishell: ");
	if (!msh)
		return ;
	first = ft_strjoin(msh, func);
	if (!first)
		return (free(msh));
	second = ft_strjoin(first, error);
	if (!second)
		return (free(msh), free(first));
	ft_putstr_fd(second, fd);
	free(first);
	free(second);
	free(msh);
}
