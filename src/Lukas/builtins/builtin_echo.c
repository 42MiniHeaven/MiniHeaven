/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:32:51 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/09 23:13:55 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

/**
 * @brief   Prints to a terminal
 *
 * Splits the input command into tokens and calls env_unset() for each variable
 * name found.
 *
 * @param   data	Structure containing the environment linked list and envp.
 * @param   cmd		Command string which should be printed to terminal
 */

int	is_valid_n_flag(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] != '-')
		return (0);
	i = 1;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(t_cmd *cmd, t_environment *list)
{
	int	i;
	int	newline;

	(void)list;
	i = 1;
	newline = 1;
	while (cmd->argv && cmd->argv[i] && is_valid_n_flag(cmd->argv[i]))
	{
		newline = 0;
		i++;
	}
	while (cmd->argv[i])
	{
		write(1, cmd->argv[i], ft_strlen(cmd->argv[i]));
		if (cmd->argv[i + 1])
			write(1, " ", 1);
		i++;
	}

	if (newline)
		write(1, "\n", 1);
	return (0);
}
