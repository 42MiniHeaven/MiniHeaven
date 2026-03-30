/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wopen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 11:13:01 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/30 18:20:48 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	wopen(const char *path, int flags, mode_t mode)
{
	int	fd;

	printf("%s\n", path);
	fd = open(path, flags, mode);
	if (fd == -1)
		fatal(path, 1);
	return (fd);
}
