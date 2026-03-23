/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 11:14:50 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/22 17:22:43 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
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

int	builtin_exit(t_cmd *cmd, t_environment *list)
{
	int	status;

	(void)list;
	ft_putstr_fd("exit\n", 1);
	if (!ft_is_numeric(cmd->argv[1]))
	{
		ft_error("exit: ", "numeric argument required\n", 2);
		exit (2);
	}
	if (cmd->argv[2])
	{
		ft_error("exit: ", "too many arguments\n", 2);
		return (1);
	}
	status = ft_atoi(cmd->argv[1]);
	return ((unsigned char)status);
}
