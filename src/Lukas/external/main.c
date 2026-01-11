/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:33:23 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/11 16:38:41 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "externals.h"

int	main(int argc, char **argv)
{
	if (argc == 1)
		return (1);
	run_external(argv);
	return (0);
}
