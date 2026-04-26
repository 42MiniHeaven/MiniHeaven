/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:09:13 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/26 16:59:17 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	ft_err_export_three(char *func, char *error, char *extra)
{
	char	*first;
	char	*second;
	char	*third;

	first = ft_strjoin("minishell: ", func);
	if (!first)
		return ;
	second = ft_strjoin(first, error);
	if (!second)
		return (free(first));
	third = ft_strjoin_three(second, "': ", extra);
	if (!third)
		return (free(first), free(second));
	ft_putendl_fd(third, 2);
	free(first);
	free(second);
	free(third);
}

void	handle_export_overflow(t_environment *list, char *str)
{
	char	*key;

	key = get_key(str);
	if (!key)
		return ;
	export_update_env(list, key);
	free(key);
}
