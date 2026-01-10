/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:23:45 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/10 21:29:15 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	single(t_cmd data)
{
	char	*argv[] = {"/usr/bin/ls", 0};
	//builtin echo hello
	//command echo hello
	(void)data;
	printf("I want to execute\n");
	execve("/usr/bin/ls", argv, NULL); //pass him a checked path
}
