/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 20:04:53 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/16 20:05:40 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "structs.h"

// Environment
t_env	*env_create_node(char *key, char *value);
t_env	*env_find(t_env *env, char *key);
int		env_init(t_environment *start, char **envp);
int		env_add(t_environment *list, t_env *node);
int		env_set(t_environment *list, t_env *node);
int		env_remove(t_environment *list, const char *key);
char	**env_arr(t_env *env);
char	**empty_env(void);
char	*get_env_value(t_env *env, char *key);
char	*get_key(const char *str);
char	*get_value(const char *str);
void	env_update(t_env *env, char *value);
void	empty_env_init(t_shell *data);

#endif