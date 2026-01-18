/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniheaven.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:23:25 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/18 19:36:37 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIHEAVEN_H
# define MINIHEAVEN_H

# include <stdio.h>					//printf
# include <unistd.h>				//write
# include <stdlib.h>				//malloc
# include <sys/types.h>				//pid_t
# include <sys/wait.h>				//waitpid
# include <readline/readline.h>
# include <readline/history.h>
# include "parser.h"

// main structure comtaining everything, which also can be freed
typedef struct	s_heaven
{
	t_token *lexer;
	t_cmd	*cmd_table;
	int		exit_code;
	char	**envp
}	t_heaven;

typedef struct	s_exec
{
	int		args;
	int		*status;
	pid_t	*process;
	int		pipefd[2];
	t_parser	
}	t_exec;

#endif
