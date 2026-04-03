/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 18:59:05 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/03 23:10:30 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

volatile sig_atomic_t	g_signal_status = 0;

/*
 * *** SIGNAL HANDLING ***
 * Handles Ctrl-C (SIGINT) and Ctrl-\ (SIGQUIT) in minishell.
 * Plays a role in the prompt (refresh on interrupt), heredoc (stop input) and 
 * execution (forward signals to child processes).
 * 
 * handle_signals() -> signals_heredoc() --> signals_exec() --> child: reset
 * --> returns to prompt mode after execution completes 
 */

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

/* //TODO
 * TO BE IMPLEMENTED
 * Ctrl+C behaviour for:
 * 		[x]Prompt mode (waiting for input)
 * 		[ ]Here-doc mode (reading << input)
 * 		[ ]Execution mode (parent + child processes)
 * 
 * During execution (before fork): ??
 * signal(SIGINT, SIG_IGN);
 * signal(SIGQUIT, SIG_IGN);
 * 
 * Child processes should restore default: ???????
 * signal(SIGINT, SIG_DFL);
 * signal(SIGQUIT, SIG_DFL);
 */

//TODO: for HEREDOC
// handle_sigint_heredoc()
// sets g_signal_status
// write("\n") + close fd
// set exit code in handle_sigint() (exit_code = 130)

void	set_exit_code(t_shell *data)
{
	data->last_exit = 128 + g_signal_status;
	g_signal_status = 0;
}

static void	handle_sigint(int sigtype)
{
	g_signal_status = sigtype;
}

static int	rl_hook(void)
{
	if (ioctl(STDIN_FILENO, TIOCSTI, "\n") == -1)
		perror("ioctl");
	rl_replace_line("", 0);
	rl_clear_history();
	return (0);
}
// ** PROMPT MODE **
/*
 * rl_hook; injects \n so readline unblocks
 * ctrl-\ = SIGQUIT; silenced at prompt
 * ctrl-c = SIGINT; sets g_signal_status
 */

void	handle_signals(void)
{
	rl_signal_event_hook = rl_hook;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}
