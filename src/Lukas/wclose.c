/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wclose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 11:20:22 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/13 12:01:53 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	wclose(int fd)
{
	if (fd >= 0)
		close(fd);
//		fatal("close", 0); // TODO: Lukas please handle
	fd = -1;
}
