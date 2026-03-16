/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:15:45 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/16 16:18:57 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniheaven.h"

t_env	*env_find(t_env *env, char *key)
{
	if (!env || !key)
		return (NULL);
	while (env != NULL)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}
