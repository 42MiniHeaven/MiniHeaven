/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 18:59:05 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/11 23:21:55 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

volatile sig_atomic_t	g_signal_status = 0;

/*
 * *** SIGNAL HANDLING ***
 * Handles Ctrl-C (SIGINT) and Ctrl-\ (SIGQUIT) in minishell.
 * Plays a role in the prompt (refresh on interrupt), heredoc (stop input) and
 * execution (forward signals to child processes).
 */

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

void	handle_signals_heredoc(void)
{
	rl_catch_signals = 0;
	rl_event_hook = rl_heredoc_hook;
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
}
