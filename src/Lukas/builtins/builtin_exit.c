/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 11:14:50 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/25 20:59:48 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static int	ft_is_numeric(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	if (ft_strcmp(str, "") == 0)
		return (0);
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i] && str[i] == '0')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

static long	ft_atol(char *nptr)
{
	int		sign;
	long	result;
	size_t	i;

	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	sign = 1;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = sign * (-1);
		i++;
	}
	result = 0;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		result = result * 10 + (nptr[i] - 48);
		i++;
	}
	return (sign * result);
}

static int	exit_validation(char *str)
{
	size_t	l[2];
	char	*max;

	while (str && *str && *str == ' ')
		str++;
	l[0] = 1;
	if (str && (str[0] == '-' || str[0] == '+'))
	{
		if (str[0] == '-')
			l[0] = 0;
		str++;
	}
	while (*str && *str == '0')
		str++;
	if (!*str)
		return (1);
	l[1] = ft_strlen(str);
	if (l[1] < 19)
		return (1);
	if (l[1] > 19 || !ft_isdigit(*str))
		return (0);
	max = "9223372036854775807";
	if (l[0] == 0)
		max = "9223372036854775808";
	return (ft_strcmp(str, max) <= 0);
}

int	builtin_exit(t_cmd *cmd, t_shell *data)
{
	long	status;

	(void)data;
	ft_putstr_fd("exit\n", 1);
	if (!cmd->argv[1])
		return (0);
	if (cmd->argv[1] && (!ft_is_numeric(cmd->argv[1])
			|| !exit_validation(cmd->argv[1])))
	{
		ft_err_three("exit: ", cmd->argv[1], "numeric argument required");
		return (2);
	}
	if (cmd->argv[2])
	{
		ft_error("exit: ", "too many arguments", 2);
		return (1);
	}
	status = ft_atol(cmd->argv[1]);
	return ((unsigned char)status);
}
