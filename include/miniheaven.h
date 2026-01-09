/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniheaven.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:23:25 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/09 21:13:49 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIHEAVEN_H
# define MINIHEAVEN_H

# include <stdio.h>			//printf
# include <unistd.h>		//write
# include <stdlib.h>		//malloc
# include <sys/types.h>		//pid_t
# include <sys/wait.h>		//waitpid

typedef struct	s_exec
{
	int		args;
	int		*status;
	pid_t	*process;
	int		pipefd[2];
}	t_exec;

#endif
