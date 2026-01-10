/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 15:09:30 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/10 17:53:52 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	EXEC_H
# define EXEC_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>

enum flag
{
	FORK,		//exec in child processes
	EXEC,		//exec in main process for builtins
	HEREDOC,
	REDIRECT,
	EMPTY,		//unused
	COUNT,
};

typedef struct s_cmd
{
	char			**argv;
	enum flag		flag;
	int				in_fd;		//default STDIN
	int				out_fd;		//default STDOUT
	struct s_cmd	*next;		//for pipes
} t_cmd;

typedef struct	s_exec
{
	int			args;
	int			*status;
	pid_t		*process;
	int			pipefd[2];
}	t_exec;

int	exec(t_cmd data);
#endif
