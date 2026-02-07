/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:01:36 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/07 21:58:50 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>
# include "../env/env.h"

typedef struct	s_cmd	t_cmd;
typedef struct	s_env	t_env;

typedef int	(*builtin_func)(t_cmd *cmd, t_env **env);		//prototype for our function

builtin_func	find_builtin(const char *name);	//Lookup function


//builting_cd
int		builtin_cd(t_cmd *cmd, t_env **env);
//builtin_echo.c
int		builtin_echo(t_cmd *cmd, t_env **env);
//builtin_env.c
int		builtin_env(t_cmd *cmd, t_env **env);
//builtin_exit.c
int		builtin_exit(t_cmd *cmd, t_env **env);
//builtin_export.c
int		builtin_export(t_cmd *cmd, t_env **env);
//builtin_pwd.c
int		builtin_pwd(t_cmd *cmd, t_env **env);
//builtin_unset.c
int		builtin_unset(t_cmd *cmd, t_env **env);
#endif
