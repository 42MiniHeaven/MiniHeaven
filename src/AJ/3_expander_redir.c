/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expander_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:43:39 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/09 23:51:23 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/miniheaven.h"

/*
** AMBIGUOUS REDIRECT — ALL CASES
**
** A redirection target is VALID only if after expansion it results in:
**     → EXACTLY ONE WORD
**
** Otherwise → "ambiguous redirect"
**
** Cases that MUST trigger ambiguous redirect:
**
** 1. Empty expansion
**    - $VAR where VAR=""
**    - $VAR where VAR is unset
**
** 2. Expansion results in ZERO words after splitting
**    - $VAR = "   " (spaces only)
**
** 3. Expansion results in MULTIPLE words
**    - $VAR = "file1 file2"
**    - > $VAR  → ["file1", "file2"]
**
** 4. Word splitting creates multiple tokens
**    - $VAR = "a   b"
**
** 5. Multiple expansions producing multiple words
**    - > $A $B
**
** 6. Globbing (*) expands to multiple files
**    - > *
**    - > $VAR where VAR="*"
**
** 7. Mixed expansions resulting in multiple tokens
**    - combinations that produce more than one word
**
** IMPORTANT RULES:
**
** - If result == 0 words  → ERROR
** - If result > 1 words   → ERROR
** - If result == 1 word   → OK
**
** QUOTES CHANGE BEHAVIOR:
**
** - "$VAR" → always ONE word (even if it contains spaces) → VALID
** - $VAR   → may split into multiple words → can be INVALID
**
** IMPLEMENTATION RULE:
**
** if (word_count != 1)
** {
**     error("ambiguous redirect");
**     return FAILURE;
** }
**
*/
char	*handle_env_var_redir(char *file, int *i, char *result, t_shell *data)
{
	int		start;
	int		j;
	char	*key;
	char	*value;
	
	key = NULL;
	value = NULL;
	start = *i + 1;
	j = start;
	while (ft_isalnum(file[j]) || file[j] == '_')
		j++;
	key = ft_substr(file, start, j - start);
	if (!key)
		return (NULL);
	value = get_env_value(data->list->head, key);
	if (!value)
		return (free(key), *i = j, file);
	result = str_join_free(result, value);
	if (!result)
		return (free(key), free(value), NULL);
	*i = j;
	return (free(key), free(value), result);
}

char	*handle_dollar_redir(t_shell *d, char *w, int *i, char *res)
{
	char	*tmp_exit; //TODO: Null the pointer

	tmp_exit = ft_itoa(d->last_exit);
	if(!tmp_exit)
		return (NULL);
	if (w[(*i) + 1] && w[(*i) + 1] == '?')
	{
		res = str_join_free(res, tmp_exit);
		(*i) += 2;
	}
	else if (ft_isalnum(w[(*i) + 1]) || w[(*i) + 1] == '_' || w[(*i) + 1] == '"')
		res = handle_env_var_redir(w, i, res, d);
	else
	{
		res = append_char(res, '$');
		(*i) += 1;
	}
	free (tmp_exit);
	return (res);
}

char	*replace_file_var(t_shell *data, char *file, char *mask)
{
	int		i;
	char	*result;

	result = NULL;
	i = 0;
	if(!file)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (file[i])
	{
		if (file[i] == '$' && mask[i] != 'S' && mask[i] != 'Q')
		{
			result = handle_dollar_redir(data, file, &i, result); 
			if (!result)
				return (NULL);
		}
		else
		{
			result = append_char(result, file[i]);
			i++;	
		}
	}
	return (result);
}

char	*expand_file_name(t_redir *tmp, char *mask, t_shell *data)
{
	char	*expanded_file;

	if (!needs_expansion_word(tmp->file, mask))
		return (tmp->file);
	expanded_file = replace_file_var(data, tmp->file, mask);
	//expand double quotes
	//expand single quotes
	return (expanded_file);
}

bool	expand_redir(t_cmd *cmd, t_shell *data)
{
	t_redir	*tmp;
	char	*mask;
	char	*result;

	tmp = cmd->redir;
	mask = NULL;
	while (tmp)
	{
		mask = create_mask(tmp->file);
		if (!mask)
			return (false);
		result = expand_file_name(tmp, mask, data);
		if (!result)
			return (false);
		// free(tmp->file); //  had the folloeing issue: Invalid free() / delete / delete[] / realloc()
		tmp->file = result; //ft_strdup(result);
		if (!tmp->file)
			return (free(mask), false);
		tmp = tmp->next;
		free(mask);
		mask = NULL;
	}
	return (true);
}

