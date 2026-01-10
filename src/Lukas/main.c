/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:50:19 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/10 17:57:46 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	main(void)
{
	char *argv[] = {"ls", "-l", NULL};

	t_cmd	cmd =
	{
		.argv = argv,
		.flag = 1,
		.in_fd = STDIN_FILENO,
		.out_fd = STDOUT_FILENO,
		.next = NULL
	};
	exec(cmd);
	return (0);
}
