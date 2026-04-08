/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 11:38:17 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/08 11:09:40 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	child_error(char *error, char *msg)
{
	write(2, "bash: ", 7);
	write(2, error, ft_strlen(error));
	write(2, msg, ft_strlen(msg));
}
