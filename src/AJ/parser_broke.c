/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lukas.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:36:14 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/26 16:15:05 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static int	cmd_add_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*head)
	{
		*head = new;
		return (1);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

static int	cmd_add_redir(t_cmd *cmd, int type, const char *file)
{
	t_redir	*new;
	t_redir	*tmp;

	new = redir_new(type, file);
	if (!new)
		return (0);
	if (!cmd->redir)
	{
		cmd->redir = new;
		return (1);
	}
	tmp = cmd->redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

int	syntax_error(char *msg)
{
	ft_putstr_fd("Syntax error: ", 2);
	ft_putendl_fd(msg, 2);
	return (-1);
}

static void	initvar(t_cmd **head, t_cmd **current, int *state, int *last_redir)
{
	*head = NULL;
	*current = NULL;
	*state = EXPECT_COMMAND;
	*last_redir = -1;
}

static int	expect_command(t_cmd **head, t_cmd **current, t_token *tok, int *state, int *last_redir)
{
	if (tok->type == WORD)
	{
		(*current) = cmd_new();
		if (!*current || !cmd_add_back(head, *current))
			return (0);
		(*current)->cmd = ft_strdup(tok->value);
		if (!(*current)->cmd || !cmd_add_arg(*current, tok->value))
			return (0);
		*state = EXPECT_ARG_OR_REDIR;
	}
	else if (tok->type >= REDIR_OUT && tok->type <= HEREDOC)
	{
		(*current) = cmd_new();
		if (!*current || !cmd_add_back(head, *current))
			return (0);
		*last_redir = tok->type;
		*state = EXPECT_REDIR_TARGET;
	}
	else
	{
		syntax_error("unexpected token");
		return (0);
	}
	return (1);
}

static int	expect_arg(t_cmd **current, t_token *tok, int *state, int *last_redir)
{
	if (*state == EXPECT_ARG_OR_REDIR)
	{
		if (tok->type == WORD)
		{
			if (!cmd_add_arg(*current, tok->value))
				return (0);
		}
		else if (tok->type >= REDIR_OUT && tok->type <= HEREDOC)
		{
			*last_redir = tok->type;
			*state = EXPECT_REDIR_TARGET;
		}
		else if (tok->type == PIPE)
		{
			if (!(*current) || !(*current)->argv[0])
			{
				syntax_error("empty command before pipe");
				return (0);
			}
			*current = NULL;
			*state = EXPECT_COMMAND;
		}
		else
		{
			syntax_error("unexpected token");
			return (0);
		}
	}
	return (1);
}

static int	expect_redir(t_cmd **current, t_token *tok, int *state, int *last_redir)
{
	if (*state == EXPECT_REDIR_TARGET)
	{
		if (tok->type != WORD)
		{
			syntax_error("expected filename");
			return (0);
		}
		if (!cmd_add_redir(*current, *last_redir, tok->value))
			return (0);
		*state = EXPECT_ARG_OR_REDIR;
	}
	return (1);
}

int	parse(t_shell *data)
{
	t_cmd	*head;
	t_cmd	*current;
	t_token	*tok;
	int		state;
	int		last_redir;

	tok = data->tokens;
	initvar(&head, &current, &state, &last_redir);
	while (tok)
	{
		if (state == EXPECT_COMMAND && !expect_command(&head, &current, tok, &state, &last_redir))
			return (0);
		else if (state == EXPECT_ARG_OR_REDIR && !expect_arg(&current, tok, &state, &last_redir))
			return (0);
		else if (state == EXPECT_REDIR_TARGET && !expect_redir(&current, tok, &state, &last_redir))
			return (0);
		tok = tok->next;
	}
	if (state == EXPECT_REDIR_TARGET)
	{
		syntax_error("unexpected end of input");
		return (0);
	}
	data->cmds = head;
	return (1);
}
