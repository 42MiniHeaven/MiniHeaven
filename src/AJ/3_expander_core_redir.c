/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expander_core_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:43:39 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/17 20:00:20 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static bool	redir_validation_check(char *file, char *value)
{
	size_t	len;
	int		i;

	len = ft_strlen(file);
	if (file[0] == '"' && file[len - 1] == '"')
		return (true);
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

static char	*handle_env_var_redir(t_shell *d, t_redir *tmp, char **res, int *i)
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
		value = "";
	if (!redir_validation_check(tmp->file, value))
		return (free(key), free(*res), *i = j, tmp->success = false, NULL);
	*res = str_join_free(*res, value);
	if (!*res)
		return (free(key), tmp->success = false, NULL);
	*i = j;
	free(key);
	return (*res);
}

static char	*handle_dollar_redir(t_shell *d, t_redir *tmp, char **res, int *i)
{
	char	*tmp_exit;

	tmp_exit = NULL;
	tmp_exit = ft_itoa(d->last_exit);
	if (!tmp_exit)
		return (NULL);
	if (tmp->file[(*i) + 1] && tmp->file[(*i) + 1] == '?')
	{
		*res = str_join_free(*res, tmp_exit);
		(*i) += 2;
	}
	else if (ft_isalnum(tmp->file[(*i) + 1]) || tmp->file[(*i) + 1] == '_'
		|| tmp->file[(*i) + 1] == '"')
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
