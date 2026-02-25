/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:37:56 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/25 19:51:15 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../../../include/miniheaven.h"

/*Function Decription:	Used to find a node in the linked list
			We need this function to return a pointer to the found value or NULL
*/

t_env	*env_find(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*get_env_value(char *key, t_env *env)
{
	t_env	*node;

	node = env_find(env, key);
	if (!node)
		return (NULL);
	return (node->value);
}
/*Function Decription: Used to create a 2 dimensional Array of the Environment
			We need this function for execve, which relays on ENVP.
*/

char	**lst_to_env(t_env *env)
{
	int		i;
	char	**envp;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp && ++i)
		tmp = tmp->next;
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			if (ft_strcmp(env->key, "_") != 0)
				envp[i++] = ft_strjoin_char(env->key, env->value, '=');
		}
		else
			envp[i++] = ft_strdup(env->key);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
