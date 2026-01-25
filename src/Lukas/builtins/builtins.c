/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:13:36 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/25 15:06:52 by lwittwer         ###   ########.fr       */
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
	{"echo", builtin_echo},
	{"env", builtin_env},
	{"exit", builtin_exit},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{NULL, NULL}
};

builtin_func	find_builtin(const char *name)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (builtins[i].name)
	{
		if (ft_strncmp(name, builtins[i].name, len) == 0)
			return (builtins[i].func);
		i++;
	}
	return (NULL);
}

