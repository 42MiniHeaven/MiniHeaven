/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:16:20 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/14 17:39:08 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*key;
	char			*value;
	int				flag;
	struct s_env	*next;
}	t_env;

typedef struct s_environment
{
	t_env	*head;
	int		size;
}	t_environment;

//create_node.c
t_env	*env_create_node(char *key, char *value, int flag);

//env_init.c
int		env_init(t_environment *start, char **envp);

//env_add.c
int		env_add(t_environment *list, t_env *node);

//env_set.c
int		env_set(t_environment *list, t_env *node);

//env_remove.c
int		env_remove(t_environment *list, const char *key);

//empty_env.c
char	**empty_env(void);

//env_utils.c
char	*get_key(const char *str);
char	*get_value(const char *str);

#endif
