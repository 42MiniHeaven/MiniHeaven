/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expander_split2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 16:49:10 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/26 16:02:49 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static void	copy_before_idx(char **new, char **argv, int idx, int *j)
{
	int	i;

	i = 0;
	while (i < idx)
	{
		new[*j] = argv[i];
		(*j)++;
		i++;
	}
}

static void	copy_split(char **new, char **split, int *j)
{
	int	i;

	i = 0;
	while (split[i])
	{
		new[*j] = split[i];
		(*j)++;
		i++;
	}
}

static void	copy_after_idx(char **new, char **argv, int idx, int *j)
{
	int	i;

	i = idx + 1;
	while (argv[i])
	{
		new[*j] = argv[i];
		(*j)++;
		i++;
	}
}

char	**argv_replace_word_with_split(char **argv, int idx, char **split)
{
	int		old_len;
	int		split_len;
	char	**new;
	int		j;

	old_len = argv_len(argv);
	split_len = argv_len(split);
	new = ft_calloc(old_len + split_len, sizeof(char *));
	if (!new)
		return (NULL);
	j = 0;
	copy_before_idx(new, argv, idx, &j);
	copy_split(new, split, &j);
	copy_after_idx(new, argv, idx, &j);
	new[j] = NULL;
	free(argv);
	free(split);
	return (new);
}

bool	needs_wordsplitting(t_cmd *cmd, char *str)
{
	char	*mask;

	if (!str)
		return (false);
	if (cmd && cmd->argv[0] && ft_strcmp(cmd->argv[0], "export") == 0)
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
