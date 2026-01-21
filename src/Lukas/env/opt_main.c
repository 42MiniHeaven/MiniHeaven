/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:07:00 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/21 13:47:02 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*File Description:	This file needs to be optimized for our merge*/

void	create_env(char **envp)
{
	t_env	*start = NULL;
	t_env	*tmp;
	char	**arr;
	size_t	i = 0;
	char	*key;
	char	*value;
	size_t	len;
	size_t	s;
	size_t	n;

	while (envp[i])
	{
		s = 0;
		while (envp[i][s] && envp[i][s] != '=')
			s++;
		n = s + 2;
		len = ft_strlen(envp[i]);
		key = ft_substr(envp[i], 0, s);
		value = ft_substr(envp[i], n, len - n);
		tmp = env_new(key, value);
		env_add_back(&start, tmp);
		i++;
	}
	arr = env_to_envp(start);
	if (!arr)
		return;
	i = -1;
	while (arr[++i])
		printf("%s\n", arr[i]);
	free_arr(arr);
	free_linked(start);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	create_env(envp);
	return (0);
}
