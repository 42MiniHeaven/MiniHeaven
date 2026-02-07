/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:05:20 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/07 17:12:02 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <aio.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>	//strcmp change later

typedef struct s_exec	t_exec;
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;
//env_utils
t_env	*env_new(char *key, char *value);
void	env_add_back(t_env **env, t_env *new);
t_env	*env_find(t_env *env, char *key);
char	*get_env_value(char *key, t_env *env);
char	**llist_to_env(t_env *env);
//env_init.c
void	create_env_list(t_env **start, char **envp);
//env_set.c
void	env_set(t_env *env, int create, char *value);
//env_unset.c
void	env_unset(t_env **env, char *cmd);
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
//ft_split
char	**ft_split(char const *s, char c);
//ft_strjoin
char	*ft_strjoin_char(char const *s1, char const *s2, char c);
#endif
