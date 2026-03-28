/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:43:39 by azielnic          #+#    #+#             */
/*   Updated: 2026/03/28 20:52:53 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

// Looks if key exists (key = whatever is writte after $)

char	*replace_var(t_shell *data, char *word, char *mask) // add shell 
{
	int		i;
	char	*tmp_exit;
	char	*result;

	if (!word)
		return (NULL);
	i = 0;
	tmp_exit = ft_itoa(data->last_exit); // We need to have this as ft_itoa allocates memory and we would get leaks if we used it directly instead of tmp;
	result = ft_strdup("");
	while (word[i])
	{
		if (word[i] == '$' && mask[i] != 'S')
		{
			if (word[i + 1] && word[i + 1] == '?')
			{
				result = str_join_free(result, tmp_exit); // join result and exit code
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
	return (result);
	// look for key using: t_env	*env_find(t_env *env, char *key)
	// once key is found value for key needs to be found: char	*get_env_value(char *key, t_env *env)
}

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

char	*join_argv(char **argv)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	if (!argv || !argv[0])
		return (NULL);
	str = ft_strdup("");
	while (argv[i])
	{
		tmp = ft_strjoin_char(str, argv[i], ' '); 
		if (!tmp)
			return (free(str), NULL);
		free(str);
		str = tmp;
		i++;
	}
	return (str);
}
