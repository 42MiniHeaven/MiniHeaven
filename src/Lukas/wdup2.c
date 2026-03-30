/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wdup2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 11:16:15 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/30 18:45:14 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	wdup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		fatal("dup2", 1);
	printf("entered\n");
}
