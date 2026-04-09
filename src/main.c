/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:54:25 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/09 13:34:32 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../include/miniheaven.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	data;
	
	check_args(argc, argv, envp);	//maybe to prevent from missuse on several ./minishell calls
	shell_init(&data, envp);		//create env
	loop(&data);					//loop calling itself 
	free_environment(data.list);	//cleanup
	return (0);
}
//TODO: LUKAS AJ handle >">" asd correct in parser/lexer and close fd in execution!
//TODO: LUKAS handle >> $HOME check in exection for EISDIR! 10_16_52

//TODO: LUKAS handle  $notexists | ls | $notexists for 11_1_5 think in execution check if cmd exists
//TODO: LUKAS handle > $notexists echo "haha" in child

