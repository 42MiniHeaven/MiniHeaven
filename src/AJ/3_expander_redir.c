/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expander_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:43:39 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/16 19:31:50 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static char	*expand_file_name(t_redir *tmp, char *mask, t_shell *data)
{
	char	*expanded_file;
	char	*trimmed_file;
	char	*expanded_mask;

	expanded_file = replace_file_var(data, tmp, mask);
	if (!expanded_file && ft_strchr(mask, 'Q'))
		return (tmp->success = true, ft_strdup(""));
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

// TODO: Lukas redir need to be also handled in the execution, checking 
// the success varaiable in the redir struct
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
		// TODO: HEREDOC check possibly not needed - check needed
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
