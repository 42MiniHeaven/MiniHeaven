/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:48:19 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/11 15:47:10 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

int	builtin_exit(char **argv)
{
	long	status;

	printf("exit\n");

	if (!argv[1])
		exit(42);		//exit from other calls
	if (!is_numeric(argv[1]))
	{
		fprintf(stderr, "exit: %s: numeric argument required\n", argv[1]);
		exit(2);
	}
	if (argv[2])
	{
		fprintf(stderr, "exit: too many arguments\n");
		return (1);
	}
	status = atol(argv[1]);
	exit((unsigned char)status);
}
