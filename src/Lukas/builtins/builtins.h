/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:01:36 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/25 15:00:45 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>

typedef struct s_exec	t_exec;

typedef int	(*builtin_func)(char **argv);		//prototype for our function

builtin_func	find_builtin(const char *name);	//Lookup function

int	builtin_exit(char **argv);
//int	builtin_cd(char **argv);

//builtin_echo.c
int		builtin_echo(char **argv);
//builtin_env.c
void	builtin_env(t_exec data, char *str);
//builtin_export.c
void	builtin_export(t_exec data, char *cmd);
//builtin_unset.c
void	builtin_unset(t_exec data, char *cmd);
#endif
