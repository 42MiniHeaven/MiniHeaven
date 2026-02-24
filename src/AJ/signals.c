/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 18:59:05 by azielnic          #+#    #+#             */
/*   Updated: 2026/02/24 21:21:16 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

#include <sys/ioctl.h>

extern volatile sig_atomic_t	g_signal_status;

/*
 * DESCRIPTION
 * The readline event hook function is used too clean up the prompt after a 
 * SIGINT (Ctrl+C).
 * The reason ioctl with TIOCSTI is used is to "force" readline to break out of 
 * its internal blocking wait by simulating an Enter key press. This moves the 
 * cursor to a new line and allows the hook to clear the buffer.
 * 
 * MORE INFORMATION
 * The ioctl() function, short for "Input/Output Control" is a system call used 
 * to perform device-specific I/O operations (that don't fit into the standard 
 * read or write categories).
 * 
 * STDIN_FILENO: This is the file descriptor for Standard Input (usually 0). 
 * It tells the system we want to perform an action on the input stream.
 * 
 * TIOCSTI: Stands for Terminal I/O Control - simulates/fakes terminal input.
 * 
 * "\n": This is the character being "pushed." In this case, it’s a newline
 * (Enter key).
 */

int	rl_hook(void)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_clear_history();
	return (0);
}
 
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
	// if (sigtype == SIGINT)
	// {
	// 	write(1, "\n", 1);
	// 	rl_on_new_line();
	// 	rl_replace_line("", 0);
	// 	rl_redisplay();
	// }
}
