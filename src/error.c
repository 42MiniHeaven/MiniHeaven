/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 13:58:11 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/21 14:31:49 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniheaven.h"

void	ft_error(char *func, char *error, int fd)
{
	ft_putstr_fd("minishell: ", fd);
	if (func)
		ft_putstr_fd(func, fd);
	if (error)
		ft_putstr_fd(error, fd);
}
