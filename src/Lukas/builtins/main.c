/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:41:06 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/11 15:48:14 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	main(int argc, char **argv)
{
	if (argc == 1)
		return (1);
	builtin_func fn = find_builtin(argv[1]);
	if (fn)
		printf("found it\n");
	else
		printf("missed it\n");
	return (0);
}
