/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:13:18 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/27 16:17:54 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	child_error(char *error, char *msg)
{
	write(2, error, ft_strlen(error));
	write(2, msg, ft_strlen(msg));
}
