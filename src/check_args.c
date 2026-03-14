/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 12:20:30 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/12 14:58:01 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniheaven.h"

/**
 * @brief Validate that the shell is started without additional arugments.
 *
 * Ensures that the program is executed only as './minishell' without any
 * extra command-line arguments. If additional arguments or unsupported
 * flags are provided, an error message is printed to 'stderr'.
 *
 * @param argc	Number of command-line arguments. Must be 1 (program name only).
 * @param argv	NULL-term array containing the command-line arguments.
 * @param envp	NULL-term array of enviroment variable from the parent shell.
 */

void	check_args(int argc, char **argv, char **envp)
{
	int	i;

	(void)envp;
	if (argc > 1)
	{
		i = 1;
		ft_putendl_fd("Invalid arguments:", 2);
		while (argv[i])
		{
			ft_putendl_fd(argv[i++], 2);
		}
	}
}
