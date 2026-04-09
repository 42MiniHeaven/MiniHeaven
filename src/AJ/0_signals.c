/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 18:59:05 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/09 19:43:18 by lwittwer         ###   ########.fr       */
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
 * 		[X]Execution mode (parent + child processes)
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

static void	handle_sig(int sigtype)
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

static int	rl_hook(void)
{
	if ( g_signal_status == SIGINT )
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_clear_history();
	}
	return (0);
}
/*
 * DESCRIPTION
 * Instead of using the default behaviour for SIGINT (SIG_DFL) - which would
 * terminate the shell on Ctrl+C - it is intercepted by handle_sig() to set
 * g_signal_status and unblock readline via the rl_hook, redisplaying a fresh
 * prompt. SIGQUIT is silenced as bash ignores it at the prompt.
 */

void	handle_signals_prompt(void)
{
	rl_signal_event_hook = rl_hook;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sig);
}

/*
 * DESCRIPTION
 * Signals are ignored in the parent as the terminal delivers them to the 
 * entire foregournd process group (all processes currently running and
 * interacting with the terminal, incl. the child). This means the child 
 * recives the signals automatically. Ignoring them in the parent prevents 
 * the shell itself from being killed while it waits for the child to finsih.
 * 
 * Setting the hook to NULL prevents it from firing outside readline.
 */

void	handle_signals_exec_parent(void)
{
	rl_signal_event_hook = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

/*
 * DESCRIPTION
 * Both signals are restored to the default kernel behaviour after fork() but
 * before execve(). This lets Ctril+C kill the child (SIGINT -> exit 130) and
 * Ctrl+\ quit the child and print "Quit (core dupmed)" (SIGQUIT -> exit 131)
 * matching the bash behaviour.
 */

void	handle_signals_exec_child(void)
{
	rl_signal_event_hook = NULL;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
//TODO: AJ check bellow!
static int    rl_heredoc_hook(void)
{
    if (g_signal_status == SIGINT )
    {

        ioctl(STDIN_FILENO, TIOCSTI, "\n");
        write(STDOUT_FILENO, "^C\n", 3);
        rl_on_new_line();//you need to specifically call this to move the cursor to a new line after the signal
        rl_replace_line("", 0);
        rl_done = 1; // This tells readline to stop waiting for input and return control to the main loop
    }
    return (0);
}

void    handle_signals_heredoc(void)
{
    rl_catch_signals = 0;
    rl_event_hook = rl_heredoc_hook;
    signal(SIGINT, handle_sig);
    signal(SIGQUIT, SIG_IGN);
}
