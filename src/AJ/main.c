/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 11:38:17 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/22 11:59:14 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

int	main(void)
{
	t_shell data;
	char	input[] = "ls -l | wc -l";

	printf("1\n");
	lexer(&data, input);
	printf("2\n");
	free_tokens(data.tokens);
	return (0);
}
