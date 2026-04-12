/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wpipe.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:23:11 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/12 23:34:50 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	wpipe(int pipefd[2], t_shell *data)
{
	if (pipe(pipefd) == -1)
		ft_error("wpipe", "could not pipe", 2);
	return ;
}
