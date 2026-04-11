/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 15:42:58 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/12 01:24:52 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

char	**env_arr(t_env *env)
{
	int		i;
	t_env	*tmp;
	char	**envp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			i++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
			envp[i++] = ft_strjoin_char(env->key, env->value, '=');
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
