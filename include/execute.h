/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:02:46 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/07 21:42:30 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <unistd.h>	//write
# include <sys/types.h>	//waitpid
# include <sys/wait.h>	//waitpid
# include "../Libft/include/libft.h"
# include "../src/Lukas/env/env.h"
# include "../src/Lukas/builtins/builtins.h"

typedef struct	s_cmd
{
	char			**argv;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_mh
{
	t_env	*llist;
	t_cmd	cmds;
	int		last_exit;
} t_mh;

//init.c
void	init_shell(t_mh *mh, char **envp);
//dispatcher.c
int		dispatcher(t_cmd *cmds, t_env *env);
//builtins.c
builtin_func	find_builtin(const char *name);
int				is_builtin(const char *name);
//free.c
void	free_arr(char **arr);
void	free_str(char *str);
void	free_linked(t_env *head);
//exec_builtin.c
int		exec_builtin(t_cmd *cmds, t_env *env);
//resolve.c
char	*resolve_path(char *cmd, t_env *env);
//forking.c
int		dispatch_pipeline(t_cmd *cmds, t_env *env);
#endif
