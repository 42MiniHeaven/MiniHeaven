/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:42:50 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/21 22:52:02 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

int	is_builtin(const char *name)
{
	if (ft_strcmp(name, "cd"))
		return (0);
	if (ft_strcmp(name, "echo"))
		return (0);
	if (ft_strcmp(name, "env"))
		return (0);
	if (ft_strcmp(name, "exit"))
		return (0);
	if (ft_strcmp(name, "export"))
		return (0);
	if (ft_strcmp(name, "pwd"))
		return (0);
	if (ft_strcmp(name, "unset"))
		return (0);
	return (1);
}
