/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:58:21 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/05 17:07:09 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/**
 * @brief   Updates an element in the environment list.
 *
 * Updates the passed elements value. Either the value of cmd or NULL.
 *
 * @param   *env	Pointer to the note to update.
 * @param   *cmd	Input string containing a key=value pair.
 */

static void	update_env(t_env *env, char *cmd)
{
	if (!cmd)
	{
		env->value = NULL;
		return ;
	}
	free(env->value);
	env->value = cmd; //maybe strdup
}

/**
 * @brief   Appends a new element to the environment list.
 *
 * Parses the given command string to extract a key-value pair,
 * creates a new environment node, and appends it to the list.
 *
 * @param   *env	Pointer to the environment list.
 * @param   *cmd	Input string containing a key=value pair.
 */

static void	add_back(t_env *env, char *cmd)
{
	t_env	*tmp;
	size_t	s;
	size_t	n;
	size_t	len;
	size_t	start;

	len = ft_strlen(cmd);
	s = 0;
	while (cmd[s] && cmd[s] != ' ')
		s++;
	s++;
	start = s;
	while (cmd[s] && cmd[s] != '=')
		s++;
	n = s + 1;
	tmp = env_new(ft_substr(cmd, start, s - start), ft_substr(cmd, n, len - n));
	env_add_back(&env, tmp);
}

/**
 * @brief   Appends or updates a linked list element.
 *
 * This function should apply changes to our MiniHeaven's environment.
 * With this function export should behave same as in BASH.
 *
 * @param   *env	either a pointer to a linked list element or NULL.
 * @param   *value	either a string or NULL.
 */

void	env_set(t_env *env, int create, char *value)
{
	if (create == 1)
		update_env(env, value);
	if (create == 2)
		add_back(env, value);
}
