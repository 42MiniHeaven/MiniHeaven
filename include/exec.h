/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 15:09:30 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/10 21:24:32 by lwittwer         ###   ########.fr       */
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
	SINGLE,		//exec in main process for builtins
	HEREDOC,
	REDIRECT,
	EMPTY,		//unused
	COUNT,
};

typedef struct s_cmd
{
	char			**argv;
	enum flag		flag;
	char			**envp;
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

int		decider(t_cmd data);
void	single(t_cmd data);
#endif
