/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:32:47 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/16 18:41:26 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

/*
 * *** PARSER ***
 * The parser takes the tokens produced by the lexer and builds a linked
 * command structure incl an array which can be passed to the execution.
 */

static bool	handle_expect_command(t_parser *p)
{
	if (p->tok->type == WORD)
	{
		p->current = cmd_new();
		if (!p->current || !cmd_add_back(&p->head, p->current))
			return (false);
		if (!cmd_add_arg(p->current, p->tok->value))
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
		return (syntax_error(p->tok->value), 0);
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
			return (syntax_error(p->tok->value), false);
		p->current = NULL;
		p->state = EXPECT_COMMAND;
	}
	else
		return (syntax_error(p->tok->value), false);
	return (true);
}

static bool	handle_expect_redir(t_parser *p)
{
	if (p->tok->type != WORD)
		return (syntax_error(p->tok->value), false);
	if (!cmd_add_redir(p->current, p->last_redir, p->tok->value))
		return (false);
	p->state = EXPECT_ARG_OR_REDIR;
	return (true);
}

static bool	parse_loop(t_parser *p)
{
	while (p->tok)
	{
		if (p->state == EXPECT_COMMAND)
		{
			if (!handle_expect_command(p))
				return (false);
		}
		else if (p->state == EXPECT_ARG_OR_REDIR)
		{
			if (!handle_expect_arg(p))
				return (false);
		}
		else if (p->state == EXPECT_REDIR_TARGET)
		{
			if (!handle_expect_redir(p))
				return (false);
		}
		p->tok = p->tok->next;
	}
	return (true);
}

int	parser(t_shell *data)
{
	t_parser	p;

	parser_init(&p, data);
	if (!parse_loop(&p))
		return (parser_exit(&p), 1);
	if (p.state == EXPECT_REDIR_TARGET)
		return (parser_exit(&p), syntax_error(data->tokens->value), 1);
	if (p.state == EXPECT_COMMAND && p.head)
		return (parser_exit(&p), syntax_error(data->tokens->value), 1);
	data->cmds = p.head;
	return (0);
}
