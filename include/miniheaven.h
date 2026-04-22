/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniheaven.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:23:25 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/22 17:53:34 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIHEAVEN_H
# define MINIHEAVEN_H

// needed for sigaction()
# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200809L
# endif

# include <stdio.h>					// printf
# include <unistd.h>				// write
# include <stdlib.h>				// malloc
# include <stdbool.h>				// boolean data type (bool)
# include <sys/types.h>				// pid_t
# include <sys/wait.h>				// waitpid
# include <fcntl.h>					// open flags
# include <errno.h>
# include <signal.h>
# include <sys/ioctl.h>				// needed for signals
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/include/libft.h"

// Minishell headers
# include "structs.h"
# include "environment.h"
# include "parser.h"
# include "expansion.h"
# include "execution.h"
# include "cleanup.h"

// General prototypes
void	loop(t_shell *data);
void	reset_shell(t_shell *data);
void	shell_init(t_shell *data, char **envp);
void	check_args(int argc, char **argv, char **envp);

char	*read_file(int fd);
# define BUFFER_SIZE 10000
#endif
