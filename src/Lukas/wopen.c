/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wopen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 11:13:01 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/07 20:17:30 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	wopen(const char *path, int flags, mode_t mode)
{
	int	fd;

	fd = open(path, flags, mode);
	return (fd);
}
