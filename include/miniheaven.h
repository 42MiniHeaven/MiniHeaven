/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniheaven.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:23:25 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/09 22:15:34 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIHEAVEN_H
# define MINIHEAVEN_H

# include <stdio.h>			//printf
# include <unistd.h>		//write
# include <stdlib.h>		//malloc
# include <sys/types.h>		//pid_t
# include <sys/wait.h>		//waitpid
# include <readline/readline.h>
# include <readline/history.h>

// idea: use enums for specific operands

// typedef enum operands
// {
	
// } ;

typedef struct	s_tokens
{
	char *token;
	t_tokens *next; // check again how linked lists work

}	t_tokens;

typedef struct	s_parser
{
	char *line;
//	char *history; // maybe an array maybe a file maybe name of file 
	char *	

}	t_parser;

typedef struct	s_exec
{
	int		args;
	int		*status;
	pid_t	*process;
	int		pipefd[2];
	t_parser	
}	t_exec;

#endif
