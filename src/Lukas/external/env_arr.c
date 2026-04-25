/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 15:42:58 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/25 21:13:00 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static char	*get_export_str(char *key, char *value)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin_char(key, "\"", '=');
	if (!tmp)
		return (NULL);
	tmp2 = ft_strjoin(tmp, value);
	if (!tmp2)
		return (free(tmp), NULL);
	free(tmp);
	tmp = NULL;
	tmp = ft_strjoin(tmp2, "\"");
	if (!tmp)
		return (free(tmp2), NULL);
	free(tmp2);
	tmp2 = NULL;
	return (tmp);
}

char	**env_arr_export(t_env *env)
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
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			envp[i++] = get_export_str(tmp->key, tmp->value);
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

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
