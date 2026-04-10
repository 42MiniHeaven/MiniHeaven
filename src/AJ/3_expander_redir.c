/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expander_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:43:39 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/10 18:30:47 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

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
** 6. Mixed expansions resulting in multiple tokens
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

//arr[0] - word or filename
//arr[1] - result
char	*handle_env_var_redir(char **arr, int *i, t_shell *data, bool *success)
{
	int		start;
	int		j;
	char	*key;
	char	*value;
	
	key = NULL;
	value = NULL;
	start = *i + 1;
	j = start;
	while (ft_isalnum(arr[0][j]) || arr[0][j] == '_')
		j++;
	key = ft_substr(arr[0], start, j - start);
	if (!key)
		return (NULL);
	value = get_env_value(data->list->head, key);
	if (!value || ft_strcmp(value, "") == 0 || (ft_strstr(value, "\"'")) 
		|| (ft_strstr(value, " \t") && !ft_strchr(arr[0], '"')))
		return (free(key), *i = j, *success = false, arr[0]);
	arr[1] = str_join_free(arr[1], value);
	if (!arr[1])
		return (free(key), free(value), *success = false, NULL);
	*i = j;
	return (free(key), free(value), arr[1]);
}

//arr[0] - word
//arr[1] - result
char	*handle_dollar_redir(t_shell *d, char**arr, int *i, bool *success)
{
	char	*tmp_exit;

	tmp_exit = NULL;
	tmp_exit = ft_itoa(d->last_exit);
	if(!tmp_exit)
		return (NULL);
	if (arr[0][(*i) + 1] && arr[0][(*i) + 1] == '?')
	{
		arr[1] = str_join_free(arr[1], tmp_exit);
		(*i) += 2;
	}
	else if (ft_isalnum(arr[0][(*i) + 1]) || arr[0][(*i) + 1] == '_' || arr[0][(*i) + 1] == '"')
		arr[1] = handle_env_var_redir(arr, i, d, success);
	else
	{
		arr[1] = append_char(arr[1], '$');
		(*i) += 1;
	}
	free (tmp_exit);
	return (arr[1]);
}

char	*replace_file_var(t_shell *data, char *file, char *mask, bool *success)
{
	int		i;
	char	*res;

	res = NULL;
	i = 0;
	if (!file)
		return (NULL);
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (file[i])
	{
		if (file[i] == '$' && mask[i] != 'S' && mask[i] != 'Q')
		{
			res = handle_dollar_redir(data, (char *[]){file, res}, &i, success); 
			if (!res)
				return (NULL);
		}
		else
		{
			res = append_char(res, file[i]);
			i++;	
		}
	}
	return (res);
}

void	redir_error()
{
	ft_putstr_fd("bash: ambiguous redirect", 2);
}

char	*expand_file_name(t_redir *tmp, char *mask, t_shell *data)
{
	char	*expanded_file;

	if (!needs_expansion_word(tmp->file, mask))
		return (tmp->file);
	expanded_file = replace_file_var(data, tmp->file, mask, &tmp->success);
	if (!expanded_file || !tmp->success)
		redir_error(); //TODO: write it and exit the program clean!!!
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

