/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 13:58:11 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/22 17:22:35 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	ft_error(char *func, char *error, int fd)
{
	ft_putstr_fd("minishell: ", fd);
	if (func)
		ft_putstr_fd(func, fd);
	if (error)
		ft_putstr_fd(error, fd);
}
