/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expander_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:43:39 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/03 21:07:49 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

/*
 * DESCRIPTION
 * Processes a dollar sign '$' encountered during varaible expansion.
 * 
 * Determines type of expansion:
 * 		- '$?' expands to the last exit status
 * 		- '$VAR' expands to the corresponding environment variable
 * 		- otherwise treats '$' as a literal character
 * 
 * BEHAVIOUR
 * @note	Appends expanded or literal content to 'res'.
 * @note	Does not perform expansion if conditions are not met.
 */

char	*handle_dollar(t_shell *d, char *w, int *i, char *res, char *exit)
{
	if (w[(*i) + 1] && w[(*i) + 1] == '?')
	{
		res = str_join_free(res, exit);
		i = i + 2;
	}
	else if (ft_isalnum(w[(*i) + 1]) || w[(*i) + 1] == '_')
		res = handle_env_var(w, i, res, d);
	else
	{
		res = append_char(res, '$');
		i++;
	}
	return (res);
}

/*
 * DESCRIPTION
 * Expands all variables in a given word based on the provided mask.
 * 
 * Iterates through the input string and replaces occurences of '$' with their
 * corresponsing values unless in single quotes. Delegates handling of '$'
 * cases to 'handle_dollar()'.
 * 
 * BEHAVIOUR
 * @note	Skips expansion when mask indicates single quotes.
 * @note	Return a newly allocated expanded string.
 */

char	*replace_var(t_shell *data, char *word, char *mask)
{
	int		i;
	char	*tmp_exit;
	char	*result;

	if (!word)
		return (NULL);
	i = 0;
	tmp_exit = ft_itoa(data->last_exit); 
	result = ft_strdup("");
	while (word[i])
	{
		if (word[i] == '$' && mask[i] != 'S')
			result = handle_dollar(data, word, &i, result, tmp_exit);
		else
		{
			result = append_char(result, word[i]);
			i++;	
		}
	}
	free (tmp_exit);
	return (result);
}

/*
 * DESCRIPTION
 * Extracts and expands an environment variable from the input word.
 * 
 * Identidies the variable name following '$', retrieves its value from the
 * environment and appends it to the result string.
 * 
 * BEHAVIOUR
 * @note	Appends empty string if variable is not found.
 */

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
