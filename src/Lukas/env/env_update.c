/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:13:30 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/12 01:23:45 by azielnic         ###   ########.fr       */
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
