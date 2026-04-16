/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 11:14:50 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/13 16:37:28 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static int	ft_is_numeric(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i] && str[i] == '0')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	builtin_exit(t_cmd *cmd, t_shell *data)
{
	int	status;

	(void)data;
	ft_putstr_fd("exit\n", 1);
	if (!cmd->argv[1])
		return (0);
	if (cmd->argv[1] && !ft_is_numeric(cmd->argv[1]))
	{
		ft_error("exit: ", "numeric argument required", 2);
		return (2);
	}
	if (cmd->argv[2])
	{
		ft_error("exit: ", "too many arguments", 2);
		return (1);
	}
	status = ft_atoi(cmd->argv[1]);
	return ((unsigned char)status);
}
