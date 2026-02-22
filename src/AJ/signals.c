/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 18:59:05 by azielnic          #+#    #+#             */
/*   Updated: 2026/02/22 22:22:36 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

extern volatile sig_atomic_t	g_signal_status;

// void	check_signals(t_shell data, char *input)
// {
// 	if (g_signal_status == SIGINT)
// 	{
// 		data.exit_code = 128 + SIGINT; // should be 130
// 		g_signal_status = 0;
// 	}
// }

/*
 * ctrl-c = SIGINT	"interrupt" displays a new prompt on a new line
 * ctrl-\ = SIGQUIT	
 * 
 */

void	handle_signals(int sigtype)
{
	g_signal_status = sigtype;
	if (sigtype == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
