/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 22:45:36 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/26 11:37:40 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static int	argv_len(char **argv)
{
	int	i = 0;

	while (argv && argv[i])
		i++;
	return (i);
}

static char	**argv_realloc(char **old, int old_len, int new_len)
{
	char	**new;
	int		i;

	new = ft_calloc(new_len, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (old && i < old_len)
	{
		new[i] = old[i]; /* transfer ownership */
		i++;
	}
	free(old);
	return (new);
}

/*
** ============================
**      COMMAND CREATION
** ============================
*/

static t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = ft_calloc(1, sizeof(char *));
	return (cmd);
}

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

/*
** ============================
**        ARGUMENTS
** ============================
*/

static int	cmd_add_arg(t_cmd *cmd, const char *word)
{
	int		len;
	char	**new;

	len = argv_len(cmd->argv);
	new = argv_realloc(cmd->argv, len, len + 2);
	if (!new)
		return (0);
	cmd->argv = new;
	cmd->argv[len] = ft_strdup(word); /* OWNED COPY */
	cmd->argv[len + 1] = NULL;
	return (1);
}

/*
** ============================
**        REDIRECTIONS
** ============================
*/

static t_redir	*redir_new(int type, const char *file)
{
	t_redir	*r;

	r = ft_calloc(1, sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = type;
	r->file = ft_strdup(file); /* OWNED COPY */
	return (r);
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

/*
** ============================
**        ERROR
** ============================
*/

int	syntax_error(char *msg)
{
	ft_putstr_fd("Syntax error: ", 2);
	ft_putendl_fd(msg, 2);
	return (-1);
}

/*
** ============================
**        PARSER
** ============================
*/
int parse(t_shell *data)
{
	t_cmd	*head = NULL;
	t_cmd	*current = NULL;
	t_token	*tok = data->tokens;
	int		state = EXPECT_COMMAND;
	int		last_redir = -1;

	while (tok)
	{
		if (state == EXPECT_COMMAND)
		{
			if (tok->type == WORD)
			{
				current = cmd_new();
				if (!current || !cmd_add_back(&head, current))
					return (0);

				current->cmd = ft_strdup(tok->value);
				if (!current->cmd
					|| !cmd_add_arg(current, tok->value))
					return (0);

				state = EXPECT_ARG_OR_REDIR;
			}
			else if (tok->type >= REDIR_OUT && tok->type <= HEREDOC)
			{
				current = cmd_new();
				if (!current || !cmd_add_back(&head, current))
					return (0);

				last_redir = tok->type;
				state = EXPECT_REDIR_TARGET;
			}
			else
			{
				syntax_error("unexpected token");
				return (0);
			}
		}
		else if (state == EXPECT_ARG_OR_REDIR)
		{
			if (tok->type == WORD)
			{
				if (!cmd_add_arg(current, tok->value))
					return (0);
			}
			else if (tok->type >= REDIR_OUT && tok->type <= HEREDOC)
			{
				last_redir = tok->type;
				state = EXPECT_REDIR_TARGET;
			}
			else if (tok->type == PIPE)
			{
				if (!current || !current->argv[0])
				{
					syntax_error("empty command before pipe");
					return (0);
				}
				current = NULL;
				state = EXPECT_COMMAND;
			}
			else
			{
				syntax_error("unexpected token");
				return (0);
			}
		}
		else if (state == EXPECT_REDIR_TARGET)
		{
			if (tok->type != WORD)
			{
				syntax_error("expected filename");
				return (0);
			}
			if (!cmd_add_redir(current,
					last_redir, tok->value))
				return (0);

			state = EXPECT_ARG_OR_REDIR;
		}
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
