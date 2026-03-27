/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2026/03/27 20:03:08 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../include/miniheaven.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	data;

	check_args(argc, argv, envp);	//maybe to prevent from missuse on several ./minishell calls
	shell_init(&data, envp);		//create env
	loop(&data);					//loop calling itself 
	restore_std_fds(data.fds);
	free_environment(data.list);	//cleanup
	return (0);
}
