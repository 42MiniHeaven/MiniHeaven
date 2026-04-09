/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expander_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 19:52:54 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/09 17:17:00 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static bool	in_str(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (true);
		i++;
	}
	return (false);
}

static int	countwords(char *input, char *delim, char *mask)
{
	int	i;
	int	check;
	int	count;

	check = 0;
	i = 0;
	count = 0;
	while (input[i])
	{
		if (!in_str(input[i], delim) && mask[i] == 'N' &&check == 0)
		{
			check = 1;
			count++;
		}
		else if (in_str(input[i], delim) && mask[i] == 'N')
			check = 0;
		i++;
	}
	return (count);
}

static char	*createnfillarr(const char *str, int start, int end)
{
	char	*ret;
	int		i;

	i = 0;
	ret = ft_calloc((end - start + 1), sizeof(char));
	if (!ret)
		return (NULL);
	while (start < end)
		ret[i++] = str[start++];
	return (ret);
}

static char	**findstartend(const char *str, char **arr, char *delim, int words, 
	char *mask)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (str[i] && k < words)
	{
		while ((str[i] && in_str(str[i], delim)) && mask[i] == 'N')
			i++;
		j = i;
		while (str[j] && !(in_str(str[j], delim) && mask[j] == 'N'))
			j++;
		if (j > i)
		{
			arr[k] = createnfillarr(str, i, j);
			if (!arr[k])
				return (free_arr(arr), NULL);
			k++;
		}
		i = j;
	}
	arr[k] = NULL;
	return (arr);
}

char	**expander_split(char *s, char *delim)
{
	int		words;
	char	**arr;
	char	*mask;

	if (!s || !delim)
		return (NULL);
	mask = create_mask(s);
	if (!mask)
		return (NULL);
	words = countwords(s, delim, mask);
	arr = ft_calloc(words + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	if (!findstartend(s, arr, delim, words, mask))
		return (NULL);
	free(mask);
	free(s);
	return (arr);
}
