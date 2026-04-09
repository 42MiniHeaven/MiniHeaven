/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:08:13 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/09 22:12:42 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_cmd			t_cmd;
typedef struct s_env			t_env;
typedef struct s_environment	t_environment;

//builtin_cd.c
int				builtin_cd(t_cmd *cmd, t_environment *list);

//builtin_echo.c
int				builtin_echo(t_cmd *cmd, t_environment *list);

//builtin_env.c
int				builtin_env(t_cmd *cmd, t_environment *list);

//builtin_exit.c
int				builtin_exit(t_cmd *cmd, t_shell *data);

//builtin_export.c
int				builtin_export(t_cmd *cmd, t_environment *list);

//builtin_pwd.c
int				builtin_pwd(t_cmd *cmd, t_environment *list);

//builtin_unset.c
int				builtin_unset(t_cmd *cmd, t_environment *list);

#endif
