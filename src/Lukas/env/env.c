/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:14:56 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/20 18:43:00 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*File Description: Functions to modify the shells environment.
			Used by: export, unset or $PATH for example
*/

/*Function Decription:	Used to create a new node for the env linked list
			Every Node consists of key, value and next.
			If we build the node with "PWD=/home/lwittwer"
			We would get:
			KEY with PWD
			VALUE with /home/lwittwer (example) or NULL
			NEXT with NULL
			We append the node later and change this pointer
*/

t_env	*env_new(char *key, char *value)
{
	t_env	node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

/*Function Decription:	Used to create the linked list.
			Every node passed should either be appended to the list,
			or be the head of the list if there is none.
*/

void	env_add_back(t_env **env, t_env *new) //add a environment to the end of the linked list
{
	t_env	*tmp;

	if (!env || !new)
		return;
	if (!*env)
	{
		*env = new;
		return;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

/*Function Decription:	Used to find a node in the linked list
			We need this function to return a pointer to the found value or NULL
*/

t_env	*env_find(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

/*Function Decription: Used to create a 2 dimensional Array of the Environment
			We need this function for execve, which relays on ENVP.
			Since we and to modify our env we want also a modified ENVP if necessary.
*/

char **env_to_envp(t_env *env)
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
			envp[i++] = ft_strjoin_three(env->key, "=", env->value);
		else
			envp[i++] = ft_strdup(env->key);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
