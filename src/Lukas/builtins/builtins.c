/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:42:50 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/23 17:54:31 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	is_builtin(const char *name)
{
	printf("entered builtin\n");
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
	printf("exited builtin\n");
	return (1);
}
