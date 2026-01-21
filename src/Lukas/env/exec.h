/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:30:59 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/21 17:52:02 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "env.h"

typedef struct s_exec
{
	t_env	*env;
	char	**envp;
	int		exit_status;
}	t_exec;

#endif
