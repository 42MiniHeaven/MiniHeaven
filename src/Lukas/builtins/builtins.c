/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:42:50 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/30 22:55:55 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	is_builtin(const char *name)
{
	if (ft_strcmp(name, "cd") == 0)
		return (0);
	if (ft_strcmp(name, "echo") == 0)
		return (0);
	if (ft_strcmp(name, "env") == 0)
		return (0);
	if (ft_strcmp(name, "exit") == 0)
		return (0);
	if (ft_strcmp(name, "export") == 0)
		return (0);
	if (ft_strcmp(name, "pwd") == 0)
		return (0);
	if (ft_strcmp(name, "unset") == 0)
		return (0);
	return (1);
}
