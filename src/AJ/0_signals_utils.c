/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_signals_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 18:59:05 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/11 23:21:49 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

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
 * STDIN_FILENO: This is the file descriptor for Standard Input (usually 0). It
 * tells the system we want to perform an action on the input stream.
 *
 * TIOCSTI: Stands for Terminal I/O Control - simulates/fakes terminal input.
 *
 * "\n": This is the character being "pushed." In this case, it’s a newline
 * (Enter key).
 *
 * So if the user presses Ctrl+C:
 * 		-The signal handler sets g_signal_status
 * 		-Readline continues waiting
 * 		-The hook injects a newline
 * 		-Readline finishes immediately
 *
 * Effect: The prompt returns instantly. Without this, Readline would still be
 * blocking.
 */

void	set_exit_code(t_shell *data)
{
	data->last_exit = 128 + g_signal_status;
	g_signal_status = 0;
}

void	handle_sig(int sigtype)
{
	g_signal_status = sigtype;
}
/*
 * DESCRIPTION
 * The Readline event hook handles asynchronous signals (e.g. SIGINT). When an
 * interrupt is detected via g_signal_status, it simulates a newline input to
 * safely break the current readline state, clears the current input line and
 * resets the history to ensure a clean prompt is displayed.
 */

int	rl_hook(void)
{
	if (g_signal_status == SIGINT)
	{
		if (ioctl(STDIN_FILENO, TIOCSTI, "\n") == -1)
			perror("ioctl");
		rl_replace_line("", 0);
	}
	return (0);
}

/*
 * DESCRIPTION
 * For the heredoc the rl_on_new_line() needs to be called to move the cursor to 
 * a new line after the signal. The rl_done tells readline to stop waiting for 
 * input and return control to the main loop.
 */

int	rl_heredoc_hook(void)
{
	if (g_signal_status == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		write(STDOUT_FILENO, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_done = 1;
	}
	return (0);
}
