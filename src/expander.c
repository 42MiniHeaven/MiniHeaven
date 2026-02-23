/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 20:07:05 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/23 22:26:46 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/miniheaven.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// input = echo $test"$lol"'lul';

void	fill_mask(char *str, char *mask, int *i, char c, char type)
{
	mask[(*i)++] = type;
	while (str[*i] && str[*i] != c)
		mask[(*i)++] = type;
	if (str[*i])
		mask[(*i)++] = type;
}
static char	*create_mask(char *str)
{
	int	i;
	char	*mask;

	mask = calloc((strlen(str) + 1), sizeof(char));
	if (!mask)
		return NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			fill_mask(str, mask, &i, '"', 'D');
		else if (str[i] == '\'')
			fill_mask(str, mask, &i, '\'', 'S');
		else
			mask[i++] = 'N';
	}
	return (mask);	
}

int	main (void)
{
	char	*str = "$test\"$lol\"'lul'hello";
	char	*mask;
	
	mask = create_mask(str);
	
	printf("Str: %s\nMask: %s", str, mask);
	return (0);
}
// static void	run_expander(char *str, t_env *env)
// {
// 	char	*mask;
// 	int		i;

// 	mask = create_mask(str);
// }

// void	expander(t_tokens *tokens, t_env *env)
// {
// 	while (tokens)
// 	{
// 		if (ft_strchr(tokens->value, "$"))
// 			run_expander(&tokens->value, env);
// 		tokens = tokens->next;
// 	}
// }
