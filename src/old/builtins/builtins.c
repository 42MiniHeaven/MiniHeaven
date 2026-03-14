/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:51:56 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/25 17:08:49 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

int	is_builtin(const char *name)
{
	if (ft_strcmp(name, "cd"))
		return (1);
	if (ft_strcmp(name, "echo"))
		return (1);
	if (ft_strcmp(name, "env"))
		return (1);
	if (ft_strcmp(name, "exit"))
		return (1);
	if (ft_strcmp(name, "export"))
		return (1);
	if (ft_strcmp(name, "pwd"))
		return (1);
	if (ft_strcmp(name, "unset"))
		return (1);
	return (0);
}
