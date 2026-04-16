/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 22:40:11 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/13 17:42:27 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	bash_error(const char *name)
{
	// TODO: to be removed as forbidden fprintf
	fprintf(stderr, "bash: %s: %s\n", name, strerror(errno));
}
