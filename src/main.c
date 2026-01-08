/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:59:07 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/04 18:18:48 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int	main(void)
{
	char	*in; //input string
	while(1)
	{
		in = readline("MiniHeaven> ");
		if (!in)
		{
			free(in); //dont know if we need this
			exit(0);
		}
		if (in)
			printf("%s\n", in); //pass to parser
		free(in);
	}
	return (0);
}
