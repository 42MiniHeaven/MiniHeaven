/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniheaven.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:23:25 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/03 17:55:26 by lwittwer         ###   ########.fr       */
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
# include "../src/Lukas/exec.h"
# include "../src/Lukas/env/env.h"

typedef struct	s_mh
{
	t_cmd	*cmd;
	t_exec	*exec;
}	t_mh;

#endif
