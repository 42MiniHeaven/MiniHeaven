/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 22:31:06 by azielnic          #+#    #+#             */
/*   Updated: 2026/01/25 18:10:20 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char **ft_realloc(char **old, size_t old_count, size_t new_count)
{
	char 	**new;
	size_t	i;
	
	new = ft_calloc(new_count, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < old_count && i < new_count)
	{
		new[i] = old[i];
		i++;
	}
	free (old); // only frees array of pointers not strings themself
	return (new);
}
int	syntax_error(char *message)
{
	ft_putstr_fd("Syntax error: ", 2);
	ft_putendl_fd(message, 2);
	return (0);
}
t_redir	*redir_new(int type, char *file)
{
	t_redir	*r;

	r = ft_calloc(1, sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = type;
	r->file = file;
	return (r);
}
int	redir_add(t_cmd *cmd, int type, char *file)
{
	t_redir *new;
	t_redir	*temp;
	
	new = redir_new(type, file);
	if (!new)
		return (0);
	if (!cmd->redir)
	{
		cmd->redir = new;
		return (1);
	}
	temp = cmd->redir;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (1);
}

int	argv_add(t_cmd *cmd, char *word)
{
	int	i;
	char *dup;
	
	i = 0;
	while (cmd->argv && cmd->argv[i])
		i++;
	dup = ft_strdup(word);
	if (!dup)
		return (0);
	cmd->argv = ft_realloc(cmd->argv, i, i + 2);
	if (!cmd->argv)
	{
		free(dup);
		return (0);
	}
	cmd->argv[i] = dup;
	cmd->argv[i + 1] = NULL;
	return (1);
}

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL; // needed? theoretically yes
	return (cmd);
}

t_cmd	*parse(t_token *tokens)
{
	t_cmd				*head;
	t_cmd				*current;
	enum e_parser_state	state;
	int					last_redir;

	head = NULL;
	current = NULL;
	state = EXPECT_COMMAND;
	last_redir = -1;
	while (tokens)
	{
		if (state == EXPECT_COMMAND)
		{
			if (tokens->type == WORD)
			{
				if (!current)
				{
					current = cmd_new();
					if (!head)
						head = current;
				}
				current->cmd = tokens->value;
				if (!argv_add(current, tokens->value))
					return (NULL);
				state = EXPECT_ARG_OR_REDIR;
			}
			else if (tokens->type >= REDIR_OUT && tokens->type <= HEREDOC)
			{
				if (!current)
				{
					current = cmd_new();
					if (!head)
						head = current;
				}
				last_redir =tokens->type;
				state = EXPECT_REDIR_TARGET;
			}
			else
			{
				syntax_error("unexpected/wrong token");
				return (NULL);
			}
		}
		else if (state == EXPECT_ARG_OR_REDIR)
		{
			if (tokens->type == WORD)
			{
				if (!argv_add(current, tokens->value))
					return (NULL);
			}
			else if (tokens->type >= REDIR_OUT && tokens->type <= HEREDOC)
			{
				last_redir = tokens->type;
				state = EXPECT_REDIR_TARGET;
			}
			else if (tokens->type == PIPE)
			{
				if (!current->cmd)
				{
					syntax_error("empty command before pipe");
					return (NULL);
				}
				current->next = cmd_new();
				current = current->next;
				state = EXPECT_COMMAND;
			}
			else
				syntax_error("unexpected token");
		}
		else if (state == EXPECT_REDIR_TARGET)
		{
			if (tokens->type != WORD)
			{
				syntax_error("expected filename after redirection");
				return (NULL);
			}
			if (!redir_add(current, last_redir, tokens->value))
				return (NULL);
			if (current->cmd)
				state = EXPECT_ARG_OR_REDIR;
			else
				state = EXPECT_COMMAND;
		}
		tokens = tokens->next;
	}
	if (state == EXPECT_REDIR_TARGET)
	{
		syntax_error("unexpected end of input; WORD needed");
		return (NULL);
	}
	return (head);
}
