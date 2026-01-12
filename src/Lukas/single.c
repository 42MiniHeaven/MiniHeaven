/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:23:45 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/12 21:13:39 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../include/exec.h"
#include "executor.h"

void	single(t_pipeline data, char **envp)
{
	(void)envp;
	//check if path
	//check if builtin
	//if builtin execute
	//else fork and execute there
	//builtin echo hello
	//command echo hello
	execve("/usr/bin/ls", data.cmds[0].argv, 0); //pass him a checked path
}
