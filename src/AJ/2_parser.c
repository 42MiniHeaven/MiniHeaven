/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:32:47 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/09 12:58:37 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

/*
 * *** PARSER ***
 * The parser takes the tokens produced by the lexer and builds a linked
 * command structure incl an array which can be passed to the execution.
 */

static void	parser_init(t_parser *p, t_shell *data)
{
	p->head = NULL;
	p->current = NULL;
	p->tok = data->tokens;
	p->state = EXPECT_COMMAND;
	p->last_redir = -1;
}

static bool	handle_expect_command(t_parser *p)
{
	if (p->tok->type == WORD)
	{
		p->current = cmd_new();
		if (!p->current || !cmd_add_back(&p->head, p->current))
			return (false);
		p->current->cmd = ft_strdup(p->tok->value);
		if (!p->current->cmd || !cmd_add_arg(p->current, p->tok->value))
			return (false);
		p->state = EXPECT_ARG_OR_REDIR;
	}
	else if (p->tok->type >= REDIR_OUT && p->tok->type <= HEREDOC)
	{
		p->current = cmd_new();
		if (!p->current || !cmd_add_back(&p->head, p->current))
			return (false);
		p->last_redir = p->tok->type;
		p->state = EXPECT_REDIR_TARGET;
	}
	else
		return (syntax_error("unexpected token"), 0);
	return (true);
}

static bool	handle_expect_arg(t_parser *p)
{
	if (p->tok->type == WORD)
	{
		if (!cmd_add_arg(p->current, p->tok->value))
			return (false);
	}
	else if (p->tok->type >= REDIR_OUT && p->tok->type <= HEREDOC)
	{
		p->last_redir = p->tok->type;
		p->state = EXPECT_REDIR_TARGET;
	}
	else if (p->tok->type == PIPE)
	{
		if (!p->current || !p->current->argv[0])
			return (syntax_error("empty command before pipe"), false);
		p->current = NULL;
		p->state = EXPECT_COMMAND;
	}
	else
		return (syntax_error("unexpected token '|'"), false);
	return (true);
}

static bool	handle_expect_redir(t_parser *p)
{
	if (p->tok->type != WORD)
		return (syntax_error("expected filename"), false);
	if (!cmd_add_redir(p->current, p->last_redir, p->tok->value))
		return (false);
	p->state = EXPECT_ARG_OR_REDIR;
	return (true);
}

int	parser(t_shell *data)
{
	t_parser	p;

	parser_init(&p, data);
	while (p.tok)
	{
		if (p.state == EXPECT_COMMAND)
		{
			if (!handle_expect_command(&p))
				return (parser_exit(&p), 1);
		}
		else if (p.state == EXPECT_ARG_OR_REDIR)
		{
			if (!handle_expect_arg(&p))
				return (parser_exit(&p), 1);
		}
		else if (p.state == EXPECT_REDIR_TARGET)
		{
			if (!handle_expect_redir(&p))
				return (parser_exit(&p), 1);
		}
		p.tok = p.tok->next;
		// if (p.state == -1) // have to check if this is needed
		// {
		// 	free_cmds(p.head);
		// 	return (NULL);
		// }	
	}
	if (p.state == EXPECT_REDIR_TARGET)
		return (parser_exit(&p), syntax_error("unexpected end of input"), 1);
	if (p.state == EXPECT_COMMAND && p.head)
		return(parser_exit(&p), syntax_error("unexpected pipe at the end"), 1);
	data->cmds = p.head;
	return (0);
}

