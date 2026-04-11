/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expander_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 19:52:54 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/12 01:01:48 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static int	countwords_mask(char *input, char *delim, char *mask)
{
	int	i;
	int	check;
	int	count;

	check = 0;
	i = 0;
	count = 0;
	while (input[i])
	{
		if (!in_str(input[i], delim) && mask[i] == 'N' && check == 0)
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

static char	*create_fill_arr(const char *str, int start, int end)
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

static int	fill_word(const char *str, char *mask, char **arr, void **context)
{
	char	*delim;
	int		*i;
	int		*k;
	int		j;

	delim = (char *)context[0];
	i = (int *)context[1];
	k = (int *)context[2];
	while ((str[*i] && in_str(str[*i], delim)) && mask[*i] == 'N')
		(*i)++;
	j = *i;
	while (str[j] && !(in_str(str[j], delim) && mask[j] == 'N'))
		j++;
	if (j > *i)
	{
		arr[*k] = create_fill_arr(str, *i, j);
		if (!arr[*k])
			return (free_arr(arr), 0);
		(*k)++;
	}
	*i = j;
	return (1);
}

static char	**findstartend(char *str, char **arr, char *delim, int words)
{
	void	*context[3];
	int		i;
	int		k;
	char	*mask;

	i = 0;
	k = 0;
	mask = create_mask(str);
	if (!mask)
		return (NULL);
	context[0] = (void *)delim;
	context[1] = (void *)&i;
	context[2] = (void *)&k;
	while (str[i] && k < words)
	{
		if (!fill_word(str, mask, arr, context))
			return (free(mask), NULL);
	}
	free(mask);
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
	words = countwords_mask(s, delim, mask);
	arr = ft_calloc(words + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	if (!findstartend(s, arr, delim, words))
		return (NULL);
	free(mask);
	free(s);
	return (arr);
}
