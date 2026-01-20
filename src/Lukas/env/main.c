/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:07:00 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/20 20:56:06 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	create_env(char **envp)
{
	t_env	start = NULL;
	t_env	tmp;
	size_t	i = 0;
	char	*key;
	char	*value;

	while (envp[i])
	{
		key = ft_substr();
		value = ft_substr();
		tmp = env_new(key, value);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	return (0);
}
