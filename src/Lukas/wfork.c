/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 11:44:02 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/04 14:03:38 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

pid_t	wfork(void)
{
	pid_t	pid;

	handle_signals_exec_parent();
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

