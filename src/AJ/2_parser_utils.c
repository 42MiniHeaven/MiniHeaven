/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parser_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 22:16:17 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/09 12:53:56 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static int	argv_len(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return (0);
	while (argv && argv[i])
		i++;
	return (i);
}

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = ft_calloc(1, sizeof(char *));
	return (cmd);
}

bool	cmd_add_arg(t_cmd *cmd, const char *word)
{
	int		len;
	char	**new;

	len = argv_len(cmd->argv);
	new = argv_realloc(cmd->argv, len, len + 2);
	if (!new)
		return (false);
	cmd->argv = new;
	cmd->argv[len] = ft_strdup(word);
	cmd->argv[len + 1] = NULL;
	return (true);
}

t_redir	*redir_new(int type, const char *file)
{
	t_redir	*r;

	r = ft_calloc(1, sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = type;
	r->file = ft_strdup(file);
	r->expand = need_heredoc_expansion(r->file);
	if (r->type == HEREDOC)
		r->file = handle_heredoc_quotes(r->file);
	return (r);
}

char	**argv_realloc(char **old, int old_len, int new_len)
{
	char	**new;
	int		i;

	new = ft_calloc(new_len, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (old && i < old_len)
	{
		new[i] = old[i];
		i++;
	}
	free(old);
	return (new);
}
