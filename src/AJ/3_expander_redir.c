/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expander_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:43:39 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/11 21:06:21 by azielnic         ###   ########.fr       */
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


// khuk@khuk-pc:~$ > $NONEXIST
// bash: $NONEXIST: ambiguous redirect
// khuk@khuk-pc:~$ export EMPTY=""
// khuk@khuk-pc:~$ > $EMPTY
// bash: $EMPTY: ambiguous redirect
// khuk@khuk-pc:~$ export TWO_WORDS="a b"
// khuk@khuk-pc:~$ > $WTO_WORDS
// bash: $WTO_WORDS: ambiguous redirect
// khuk@khuk-pc:~$ 

// azielnic@c2r5p14:~$ export TEST="x y"
// azielnic@c2r5p14:~$ echo $TEST
// x y
// azielnic@c2r5p14:~$ > $TEST
// bash: $TEST: ambiguous redirect
// azielnic@c2r5p14:~$ > "$TEST"
// azielnic@c2r5p14:~$ ls
//  42_minishell_tester   Evaluations   MiniHeaven   Public       test.c
//  Desktop	       exam_prep     Music	  sgoinfre     Videos
//  Documents	       fract-ol      Pictures	  src_github  'x y'
//  Downloads	       goinfre	     Piscine	  Templates
// azielnic@c2r5p14:~$ > '$TEST'
// azielnic@c2r5p14:~$ ls
// '$TEST'		       Downloads     goinfre	  Piscine      Templates
//  42_minishell_tester   Evaluations   MiniHeaven   Public       test.c
//  Desktop	       exam_prep     Music	  sgoinfre     Videos
//  Documents	       fract-ol      Pictures	  src_github  'x y'
// azielnic@c2r5p14:~$ 

bool	redir_validation_check(char *file, char *value)
{
	size_t	len;
	int		i;

	// if filename is in double quotes all will be expanded and printed -> true
	len = ft_strlen(file);
	if (file[0] == '"' && file[len - 1] == '"')
		return (true);
	// if value consists of two or more words and filename is NOT in double quotes -> false
	i = 0;
	while (ft_isspace(value[i]))
		i++;
	if (value[i] == '\0')
		return (false);
	while (value[i] && !ft_isspace(value[i]))
		i++;
	if (value[i] == '\0')
		return (true);
	while (ft_isspace(value[i]))
		i++;
	if (value[i] != '\0')
		return (false);
	return (true);
}

char	*handle_env_var_redir(t_shell *d, t_redir *tmp, char **res, int *i)
{
	int		start;
	int		j;
	char	*key;
	char	*value;
	
	key = NULL;
	value = NULL;
	start = *i + 1;
	j = start;
	while (ft_isalnum(tmp->file[j]) || tmp->file[j] == '_')
		j++;
	key = ft_substr(tmp->file, start, j - start);
	if (!key)
		return (NULL);
	value = get_env_value(d->list->head, key);
	if (!value || ft_strcmp(value, "") == 0)
		return (free(key), free(*res), *i = j, tmp->success = false, NULL);
	if (!redir_validation_check(tmp->file, value))
		return (free(key), free(*res), *i = j, tmp->success = false, NULL);
	*res = str_join_free(*res, value);
	if (!*res)
		return (free(key), tmp->success = false, NULL);
	*i = j;
	return (free(key), *res);
}

char	*handle_dollar_redir(t_shell *d, t_redir *tmp, char **res, int *i)
{
	char	*tmp_exit;

	tmp_exit = NULL;
	tmp_exit = ft_itoa(d->last_exit);
	if(!tmp_exit)
		return (NULL);
	if (tmp->file[(*i) + 1] && tmp->file[(*i) + 1] == '?')
	{
		*res = str_join_free(*res, tmp_exit);
		(*i) += 2;
	}
	else if (ft_isalnum(tmp->file[(*i) + 1]) || tmp->file[(*i) + 1] == '_' || tmp->file[(*i) + 1] == '"')
		*res = handle_env_var_redir(d, tmp, res, i);
	else
	{
		*res = append_char(*res, '$');
		(*i) += 1;
	}
	free (tmp_exit);
	return (*res);
}

char	*replace_file_var(t_shell *data, t_redir *tmp, char *mask)
{
	int		i;
	char	*res;

	res = NULL;
	i = 0;
	if (!tmp->file)
		return (NULL);
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (tmp->file[i])
	{
		if (tmp->file[i] == '$' && mask[i] != 'S' && mask[i] != 'Q')
			res = handle_dollar_redir(data, tmp, &res, &i); 
		else
		{
			res = append_char(res, tmp->file[i]);
			i++;	
		}
		if (!res)
			return (NULL);
	}
	return (res);
}

void	redir_error(t_redir *tmp)
{
	ft_error(tmp->file ,": ambiguous redirect", 2);
	free(tmp->file);
	tmp->file = NULL;
}

char	*expand_file_name(t_redir *tmp, char *mask, t_shell *data)
{
	char	*expanded_file;
	char	*trimmed_file;
	char	*expanded_mask;

	expanded_file = replace_file_var(data, tmp, mask);
	if (!expanded_file || !tmp->success)
		return (redir_error(tmp), NULL);
	expanded_mask = create_mask(expanded_file);
	if (!expanded_mask)
		return (free(expanded_file), redir_error(tmp), NULL);
	trimmed_file = remove_quotes(expanded_file, expanded_mask);
	free(expanded_mask);
	free(expanded_file);
	if (!trimmed_file || trimmed_file[0] == '\0')
		return (free(trimmed_file), redir_error(tmp), NULL);
	return (trimmed_file);
}
// TODO: redir need to be also handled in the execution, checking the success varaiable in the redir struct
// could be made a void as it doesn't catch anything
bool	expand_redir(t_cmd *cmd, t_shell *data)
{
	t_redir	*tmp;
	char	*mask;
	char	*result;

	tmp = cmd->redir;
	mask = NULL;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			tmp = tmp->next;
			continue ;
		}
		mask = create_mask(tmp->file);
		if (!mask)
			return (ft_error("malloc failed for mask", NULL, 2), false);
		result = expand_file_name(tmp, mask, data);
		if (!result)
			return (free(mask), false);
		free(tmp->file);
		tmp->file = result;
		if (!tmp->file)
			return (free(mask), false);
		tmp = tmp->next;
		free(mask);
		mask = NULL;
	}
	return (true);
}

