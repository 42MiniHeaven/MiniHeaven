/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expander_split2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 16:49:10 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/09 17:16:30 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

char **argv_replace_word_with_split(char **argv, int idx, char **split)
{
    int oldlen;
    int splitlen;
    char **new;
    char **tmp;
    int i;
    int j;

    oldlen = argv_len(argv);
    splitlen = argv_len(split);
    new = ft_calloc(oldlen + splitlen, sizeof(char *));
    if (!new)
        return (NULL);
    i = 0;
    j = 0;
    while (i < idx)
        new[j++] = argv[i++];
    tmp = split;
    while (*tmp)
        new[j++] = *tmp++;
    i++;
    while (argv[i])
        new[j++] = argv[i++];
    new[j] = NULL;
    return (free(argv), free(split), new);
}

bool	needs_wordsplitting(char *str)
{
	char	*mask;

	if (!str)
		return (false);
	mask = create_mask(str);
	if (!mask)
		return (false);
	if (ft_strchr(str, '$') && ft_strchr(mask, 'N'))
	{
		free(mask);
		return (true);
	}
	free(mask);
	return (false);
}
