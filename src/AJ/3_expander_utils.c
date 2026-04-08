/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expander_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 21:22:36 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/08 17:44:20 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

bool	needs_wordsplitting(char *str, int *error)
{
	char	*mask;

	mask = create_mask(str);
	printf("Mask: %s\n", mask);
	if (!mask)
		*error = -1;
	printf("Token entering check: %s\n", str);	
	if (ft_strchr(mask, 'N'))
		return (true);
	free(mask);
	return (false);
}

/*
 * Explain why +2 (one for the char c and one for the null terminator)
 */

char	*append_char(char *str, char c)
{
	char	*new;
	int		len;

	if(!str)
		return (NULL);
	len = ft_strlen(str);
	new = ft_calloc(len + 2, sizeof(char));
	if (!new)
	{
		free(str);
		return (NULL);
	}
	ft_memcpy(new, str, len);
	new[len] = c;
	free(str);
	return(new);
}

char	*str_join_free(char *str1, char *str2)
{
	char	*new;
	int		len1;
	int		len2;
	
	if (!str1 || !str2)
		return (NULL);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	new = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!new)
	{
		free(str1);
		return (NULL);
	}
	ft_memcpy(new, str1, len1);
	ft_memcpy(new + len1, str2, len2);
	new[len1 + len2] = '\0';
	free(str1);
	return (new);	
}

char	*join_argv(char **argv)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	if (!argv || !argv[0])
		return (NULL);
	str = ft_strdup("");
	while (argv[i])
	{
		tmp = ft_strjoin_char(str, argv[i], ' '); 
		if (!tmp)
			return (free(str), NULL);
		free(str);
		str = tmp;
		i++;
	}
	return (str);
}
