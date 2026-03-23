/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:13:30 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/22 17:22:43 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	env_update(t_env *env, char *value)
{
	if (!env)
		return ;
	if (!value)
	{
		free(env->value);
		env->value = NULL;
		env->flag = 1;
		return ;
	}
	free(env->value);
	env->value = ft_strdup(value);
	if (env->key && env->value)
		env->flag = 0;
}
