/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:05:20 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/20 19:58:04 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;

t_env	*env_new(char *key, char *value);
void	env_add_back(t_env **env, t_env *new);
t_env	*env_find(t_env *env, char *key);
char	**env_to_envp(t_env *env);

#endif
