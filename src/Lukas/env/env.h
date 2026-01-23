/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:05:20 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/23 16:07:49 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <aio.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>	//strcmp change later

typedef struct s_exec t_exec;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

void	create_env(t_env **start, char **envp);
t_env	*env_new(char *key, char *value);
void	env_add_back(t_env **env, t_env *new);
t_env	*env_find(t_env *env, char *key);
char	**env_to_envp(t_env *env);
//builtin_env.c
void	builtin_env(t_exec data, char *str);
//free.c
void	free_arr(char **arr);
void	free_str(char *str);
void	free_linked(t_env *head);
//builtin_export.c
void	builtin_export(t_exec data, char *cmd);
//ft_substr
char	*ft_substr(char const *s, unsigned int start, size_t len);
//ft_calloc
void	*ft_calloc(size_t nmemb, size_t size);
//ft_bzero
void	ft_bzero(void *s, size_t n);
//ft_strlen
size_t	ft_strlen(const char *s);
//ft_strdup
char	*ft_strdup(const char *s);
//ft_strncmp
int		ft_strncmp(const char *s1, const char *s2, size_t n);
//ft_strjoin_env
char	*ft_strjoin_env(char const *s1, char const *s2);
//ft_putstr_fd
void	ft_putstr_fd(char *s, int fd);
//ft_strchr
char	*ft_strchr(const char *s, int c);
#endif
