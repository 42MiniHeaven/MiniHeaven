/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:48:19 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/07 22:12:57 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
//#include "../env/env.h"
#include "../../../include/execute.h"

static int	is_numeric(char *s)
{
	int	i = 0;
	if (!s)
		return (0);
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_cmd *cmd, t_env **env)
{
	long	status;

	(void)env;
	printf("exit\n");
	if (!cmd->argv[1])
		exit(42);		//exit from other calls
	if (!is_numeric(cmd->argv[1]))
	{
		fprintf(stderr, "exit: %s: numeric argument required\n", cmd->argv[1]);
		exit(2);
	}
	if (cmd->argv[2])
	{
		fprintf(stderr, "exit: too many arguments\n");
		return (1);
	}
	status = atol(cmd->argv[1]);
	exit((unsigned char)status);
}
