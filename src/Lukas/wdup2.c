/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wdup2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 11:16:15 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/17 17:40:34 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	wdup2(int oldfd, int newfd)
{
	int	check;

	if (oldfd < 0 || newfd < 0)
		return (-1);
	check = dup2(oldfd, newfd);
	if (check == -1)
		return (-1);
	return (0);
}
