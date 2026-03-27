/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 19:52:54 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/27 21:23:57 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static int	in_str(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

static int	countwords(char *input, char *delim)
{
	int	i;
	int	check;
	int	count;

	check = 0;
	i = 0;
	count = 0;
	while (input[i])
	{
		if (!in_str(input[i], delim) && check == 0)
		{
			check = 1;
			count++;
		}
		else if (in_str(input[i], delim))
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
	{
		ret[i++] = str[start++];
	}
	return (ret);
}

static char	**findstartend(const char *str, char **arr, char *delim, int words)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (str[i] && k < words)
	{
		while (str[i] && in_str(str[i], delim))
			i++;
		j = i;
		while (str[j] && !in_str(str[j], delim))
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

	if (!s || !delim)
		return (NULL);
	words = countwords(s, delim);
	arr = ft_calloc(words + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	if (!findstartend(s, arr, delim, words))
		return (NULL);
	return (free(s), arr);
}
