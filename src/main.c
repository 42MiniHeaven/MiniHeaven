/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:54:25 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/27 11:43:14 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniheaven.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	data;
	int		i;

	i = 0;
	check_args(argc, argv, envp);
	shell_init(&data, envp);
	loop(&data);
	i = data.last_exit;
	free_environment(data.list);
	wclose(0);
	wclose(1);
	wclose(2);
	return (i);
}
