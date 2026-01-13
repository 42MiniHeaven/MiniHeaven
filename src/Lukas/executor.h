/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:33:04 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/13 15:18:34 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct	s_command
{
	char	**argv;
	char	*input_file;
	char	*output_file;
	int		append;
} t_command;

typedef struct	s_pipeline
{
	t_command	*cmds;
	int			count;
} t_pipeline;

int		decider(t_pipeline data, char **envp);
void	single(t_pipeline data, char **envp);

//path_utils
char	*ret_unresolved(char **envp);
char	**ret_patharr(char *env);

//path_confirm
char	*ret_absolute(char *cmd);
char	*ret_builtabsolute(char *cmd, char **dirs);
int		is_executable(const char *path);
#endif
