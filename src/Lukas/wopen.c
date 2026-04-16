/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wopen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 11:13:01 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/16 18:43:02 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	wopen(const char *path, int flags, mode_t mode)
{
	int		fd;
	char	*err;
	
	fd = open(path, flags, mode);
	if (fd < 0)
	{
		err = ft_strjoin(": ", strerror(errno));
		if (!err)
			return (-1);
		ft_error((char *)path, err, 2);
		free(err);
		return (-1);
	}
	return (fd);
}
