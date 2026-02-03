/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:02:46 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/03 22:24:12 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../src/Lukas/env/env.h"
# include "../Libft/include/libft.h"
# include "../src/Lukas/builtins/builtins.h"

typedef struct s_mh
{
	char	**env;
	t_env	*llist;
	char	**cmd;
	int		last_exit;
} t_mh;

//init.c
void	init_shell(t_mh *data, char **envp);
//execute.c
int		execute(char **cmds, char **env);
//builtins.c
builtin_func	find_builtin(const char *name);
int				is_builtin(const char *name);
#endif
