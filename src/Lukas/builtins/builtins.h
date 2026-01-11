/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:01:36 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/11 15:58:56 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>

typedef int	(*builtin_func)(char **argv);		//prototype for our function

builtin_func	find_builtin(const char *name);	//Lookup function

int	builtin_exit(char **argv);
//int	builtin_cd(char **argv);

#endif
