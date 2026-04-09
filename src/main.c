/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:54:25 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/09 17:35:40 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	data;

	check_args(argc, argv, envp);	//maybe to prevent from missuse on several ./minishell calls
	shell_init(&data, envp);		//create env
	loop(&data);					//loop calling itself 
	free_environment(data.list);	//cleanup
//	free_fds(data.fds);
	return (0);
}
