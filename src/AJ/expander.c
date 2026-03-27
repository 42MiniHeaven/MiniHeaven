/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:43:39 by azielnic          #+#    #+#             */
/*   Updated: 2026/03/23 17:17:44 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

// Before the head is returned to the main including the commands for the execution
// expansion needs to happen.

// Checks for $, handles quotes and removes quotes and replaces it with the expansion.
// 1. Single quotes: Trims quotes only
// 2. Double quotes: Trims quotes and expands varaiable
// 3. No quotes: Expands and splits words
// SPECIAL CASE: HEREDOC
// At some point in the expander it needs to be checked with redirections there are. 
// For heredoc:
// $hi -> does not expand
// "$hi" -> trims quotes only, $ stays
// '$hi' -> trims quotes only, $ stays

// struct	s_shell
// {
// 	t_token *tokens;
// 	t_cmd	*cmds;
// 	int		exit_code;
// 	int		last_signal;
// 	t_env	*llist;
// 	t_fds	*fds;
// }

// struct s_cmd 
// {
// 	char        *cmd;	// command only
// 	char		**argv;	// flags ["-l", NULL], dymanic uses realloc
// 	t_redir		*redir; // linked list of redirections
// 	t_cmd       *next;  // next command in pipeline
// }

// ------------------------------------------------------------------------

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

/*
 * DESCRIPTION
 * Exists for the remove_quotes funtion to check the length of the new string without the quotes. 
 * It uses the mask and substracts the number of quotes.
 */

int	count_len(char *mask)
{
	int	i;
	int	len;
	
	i = 0;
	len = 0;
	while (mask[i])
	{
		if (mask[i] != 'Q')
			len++;
		i++;
	}
	return(len);
}

char	*remove_quotes(char *word, char *mask)
{
	int		i;
	int		j;
	char	*result;
	
	i = 0;
	j = 0;
	result = ft_calloc(count_len(mask) + 1, sizeof(char));
	if (!result)
		return (NULL); // do we need an error?
	while (word[j] && mask[j])
	{
		while (mask[j] && mask[j] == 'Q')
			j++;
		result[i] = word[j];
		i++;
		j++;
	}
	return (result);
}

char	*handle_env_var(char *word, int *i, char *result, t_shell *data)
{
	int		start;
	int		j;
	char	*key;
	char	*value;
	
	start = *i + 1;
	j = start;
	while (ft_isalnum(word[j]) || word[j] == '_')
		j++;
	key = ft_substr(word, start, j - start);
	value = get_env_value(data->list->head, key);
	if (!value)
		value = "";
	result = str_join_free(result, value);
	free(key);
	*i = j;
	return (result);
}

/*
 * DESCRIPTION
 * Goes through the string which could contain more than one $, meaning also $ in single
 * quotes could be present. This also has to be handled.
 */
// Looks if key exists (key = whatever is writte after $)

char	*expand_var(t_shell *data, char *word, char *mask)
{
	int		i;
	char	*tmp_exit;
	char	*result;

	i = 0;
	tmp_exit = ft_itoa(data->last_exit); // We need to have this as ft_itoa allocates memory and we would get leaks if we used it directly instead of tmp;
	result = ft_strdup("");
	while (word[i])
	{
		if (word[i] == '$' && mask[i] != 'S') // could be exported to handles expandable_dollar()
		{
			if (word[i + 1] && word[i + 1] == '?')
			{
				result = str_join_free(result, tmp_exit);
				i = i + 2;
			}
			else if (ft_isalnum(word[i + 1]) || word[i + 1] == '_')
				result = handle_env_var(word, &i, result, data); // look up var
			else
			{
				result = append_char(result, '$');
				i++;
			}
		}
		else
		{
			result = append_char(result, word[i]);
			i++;	
		}
	}
	free (tmp_exit);
	free(word);
	return (result);
	// look for key using: t_env	*env_find(t_env *env, char *key)
	// once key is found value for key needs to be found: char	*get_env_value(char *key, t_env *env)
}

void	fill_mask(char *str, char *mask, int *i, char c, char type)
{
	mask[(*i)++] = 'Q';
	while (str[*i] && str[*i] != c)
		mask[(*i)++] = type;
	if (str[*i])
		mask[(*i)++] = 'Q';
}

static char	*create_mask(char *str)
{
	int		i;
	char	*mask;

	mask = ft_calloc((strlen(str) + 1), sizeof(char));
	if (!mask)
		return NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			fill_mask(str, mask, &i, '"', 'D');
		else if (str[i] == '\'')
			fill_mask(str, mask, &i, '\'', 'S');
		else
			mask[i++] = 'N';
	}
	return (mask);	
}

/*
 * DESCRIPTION
 * Checks if word contains $ and if yes, if the $ is not in single quotes.
 * Returns either 0 or 1 (false or true).
 */

bool	needs_expansion(char *word, char *mask)
{
	int i;
	int needed;
	
	i = 0;
	needed = false;
	if (ft_strchr(word, '$') != NULL)
	{
		while (word[i] && mask[i])
		{
			if (word[i] == '$' && mask[i] != 'S')
				needed = true;
			i++;
		}
	}
	return (needed);
}

bool	expand_word(t_shell *data, char *word)
{
	char	*mask;

	mask = NULL;
	mask = create_mask(word);
	if (!mask)
		return (false);
	if (needs_expansion(word, mask))
		word = expand_var(data, word, mask);
	if (!word)
		return (false);
	free(mask);
	mask = NULL;
	mask = create_mask(word);
	printf("New mask: %s\n", mask);
	if (!mask)
		return (false);
	// word splittling & check if expansion needed
	word = remove_quotes(word, mask);
		
	// also word splitting if needed
	// The space, tab and newline are used to separate values when word splitting.
	
	free(mask);
	return (true);
}

/*
 * DESCRIPTION
 * Calls expanders for all command nodes (command string, argument list(argv)
 * and redirection targets).
 */

void	expand_cmd(t_cmd *cmd, t_shell *data)
{
	int	i;

	i = 0;
	while (cmd->argv[i]) // if or while??
	{
		if (!expand_word(data, cmd->argv[i]))
			return ; // handle malloc failure
		i++;
	}
	// if (cmd->argv)
	// 	expand_agrs(cmd->argv, data); // needs to be created
	// if (cmd->redir)
	// 	expand_redir(cmd->redir, data); // needs to be created
}

/*
 * DESCRIPTION
 * Iterates throuh the command list stored in the t_shell struct and performs
 * expansion on each command node. Calls expand_cmd() for every command in
 * the pipeline.
 *  ?????Protects heredoc delimiters from expanding.
 *
 * VARAIABLES
 * t_cmd *tmp_cmd is a temporary pointer which is used not to destroy the 
 * head pointer of data->cmds itself.
 */

 // How should redirections be handles here??? Should there genereally be
 // be a special case for redirections??

void	expand_commands(t_shell *data)
{
	t_cmd	*tmp_cmd;
	
	if (!data || !data->cmds)
		return ;
	tmp_cmd = data->cmds;
	while (tmp_cmd)
	{
		expand_cmd(tmp_cmd, data);
		tmp_cmd = tmp_cmd->next;
	}
}
