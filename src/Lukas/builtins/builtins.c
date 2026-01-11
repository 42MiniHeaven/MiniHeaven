/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:13:36 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/11 15:58:45 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

typedef struct
{
	const char	*name;
	builtin_func	func;
} builtin;

static builtin	builtins[] = 
{
//	{"cd", builtin_cd},
	{"exit", builtin_exit},
	{NULL, NULL}
};

builtin_func	find_builtin(const char *name)
{
	int	i;

	i = 0;
	while (builtins[i].name)
	{
		if (strcmp(name, builtins[i].name) == 0)
			return (builtins[i].func);
		i++;
	}
	return (NULL);
}

