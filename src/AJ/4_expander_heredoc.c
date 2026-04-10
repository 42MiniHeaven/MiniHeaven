/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_expander_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 20:28:03 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/10 15:29:17 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

// For heredoc:
// $hi -> does not expand
// "$hi" -> trims quotes only, $ stays
// '$hi' -> trims quotes only, $ stays

static char	*replace_var_heredoc(t_shell *data, char *word)
{
	int	i;
	char	*tmp_exit;
	char	*result;

	if (!word)
		return (NULL);
	i = 0;
	tmp_exit = ft_itoa(data->last_exit);
	result = ft_strdup("");
	while (word[i])
	{
		if (word[i] == '$')
			result = handle_dollar(data, word, &i, result, tmp_exit);
		else
		{
			result = append_char(result, word[i]);
			i++;
		}
	}
	free(tmp_exit);
	return (result);
}

char	*expand_line(t_shell *data, char *input)
{
	//just check the word after $ for expansion
	char	*ret;

	ret = replace_var_heredoc(data, input);
	return (ret);
}
