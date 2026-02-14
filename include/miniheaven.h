/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniheaven.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:23:25 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/14 14:10:31 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIHEAVEN_H
# define MINIHEAVEN_H

# include <stdio.h>					// printf
# include <unistd.h>				// write
# include <stdlib.h>				// malloc
# include <sys/types.h>				// pid_t
# include <sys/wait.h>				// waitpid
# include <fcntl.h>					// open flags
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../../Libft/include/libft.h"
# include "parser.h"
# include "../src/Lukas/env/env.h"
# include "../src/Lukas/builtins/builtins.h"

// Maybe delete later
# include <aio.h>
# include <ctype.h>

typedef struct	s_shell	t_shell;
typedef struct	s_fd t_fd;

// main structure comtaining everything, which also can be freed easily
struct	s_shell
{
	t_token *tokens;
	t_cmd	*cmds;
	int		exit_code;
	t_env	*envp;
	int		last_signal
};

struct s_fd
{
	int	in;
	int	out;
	int	err;
};

#endif