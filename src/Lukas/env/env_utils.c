/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:14:56 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/14 21:26:27 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../../include/miniheaven.h"

/*File Description: Functions to modify the shells environment.
			Used by: export, unset or $PATH for example
			Environment handling (Day 1–2)
			Internal env stored as linked list.
			Converted to envp only for execve.
			Order preserved. Ownership clear.*/

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
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	if (node->value)
		node->is_exported = 0;
	else
		node->is_exported = 1;
	node->next = NULL;
	return (node);
}

/*Function Decription:	Used to create the linked list.
			Every node passed should either be appended to the list,
			or be the head of the list if there is none.
*/

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!env || !new)
		return ;
	if (!*env)
	{
		*env = new;
		return ;
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
	size_t	len;

	len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->key, key, len) == 0 && env->key[len] == '\0')
			return (env);
		env = env->next;
	}
	return (NULL);
}

/*
*/

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

char	**llist_to_env(t_env *env)
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
			envp[i++] = ft_strjoin_char(env->key, env->value, '=');
		else
			envp[i++] = ft_strdup(env->key);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
