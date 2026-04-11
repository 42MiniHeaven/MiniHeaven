/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wpipe.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:23:11 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/12 01:47:32 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	wpipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		return ;
//		fatal("pipe", 1); // TODO: Lukas handle please
}
