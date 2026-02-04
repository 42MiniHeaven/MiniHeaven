/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 22:31:06 by azielnic          #+#    #+#             */
/*   Updated: 2026/02/04 22:36:21 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
 * 	IDEA: 	Either all information from the lexer is duplicated or borrowed.
 * 			This is important when it comes to freeing.
 * 			Parser in our case borrows everything. Pointers are stored directly
 * 			and no strdup is used. Tokens sray alive until execution finishes.
 * 			
 * IMPORTANT: !!The tokens are also freed last AFTER EXECUTION FINISHES!!
 * 				This causes the parser and lexer to be connected and not
 * 				independant which is ok.
 *
 * 	Memory usage:	input
 *					→ lexer creates tokens
 *					→ parser builds AST using token pointers
 *					→ executor runs commands
 *					→ free AST (not strings)
 *					→ free tokens (strings freed here)
 *
 */

/*
 * INFO:	Only what was allocated needs to be freed. Only the t_redir
 *			contiguous block is allocated. the int is not dynamically
 *			allocated so also does not need to be freed. The other two are
 *			pointers (pointing to allocated memory somewhere but are not
 *			allocated themselves). The content of the pointers is feed 
 *			somehwere else.
 * 
 * 			t_redir includes:	-type (int)
 *								-file (char *)
 *								-next (t_redir *)		
 */

void	free_redirs(t_redir *redir)
{
	t_redir	*next;
	
	while (redir)
	{
		next = redir->next;
		free(redir);
		redir = next;
	}
}
 
void	free_cmds(t_cmd *cmd)
{
	t_cmd	*next;
	
	while (cmd)
	{
		next = cmd->next;
		// if (cmd->cmd)
		// 	free(cmd->cmd);
		if (cmd->argv)
			free(cmd->argv);
		if (cmd->redir)
			free_redirs(cmd->redir);
		free(cmd);
		cmd = next;
	}
}

void	free_tokens(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		free(token->value);
		free(token);
		token = next;
	}
}

/*
 * GENERAL: Cleaning funtion which first destroys all parser output and then
 * 			all lexer output.
 */

void	destroy_all(t_cmd *cmds, t_token *tokens)
{
	free_cmds(cmds);
	free_tokens(tokens);
}

/////////////// destroy functions above will get tehir own file ///////////////////
 
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
	
	if (!cmd)
		return (0);
	i = 0;
	while (cmd->argv && cmd->argv[i])
		i++;
	cmd->argv = ft_realloc(cmd->argv, i, i + 2);
	if (!cmd->argv)
		return (0);
	cmd->argv[i] = word;
	cmd->argv[i + 1] = NULL;
	return (1);
}

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	return (cmd);
}
void	init_command(t_cmd **head, t_cmd **current)
{
	*current = cmd_new();
	if (!*head)
		*head = *current;
}

int	handle_redir_target(int state, t_cmd **current, int *last_redir, 
	t_token *tokens)
{
	if (tokens->type != WORD)
	{
		syntax_error("expected filename after redirection");
		return (-1); // how to hanlde the error?
	}
	if (!redir_add(*current, *last_redir, tokens->value))
		return (-1); // how to hanlde the error?
	if ((*current)->cmd)
		state = EXPECT_ARG_OR_REDIR;
	else
		state = EXPECT_COMMAND;
	return (state);
}

int	handle_arg_or_redir(int state, t_cmd **current, int *last_redir, 
	t_token *tokens)
{
	if (tokens->type == WORD)
	{
		if (!argv_add(*current, tokens->value))
			return (-1); // how to hanlde the error?
	}
	else if (tokens->type >= REDIR_OUT && tokens->type <= HEREDOC)
	{
		*last_redir = tokens->type;
		state = EXPECT_REDIR_TARGET;
	}
	else if (tokens->type == PIPE)
	{
		if (!(*current)->cmd)
		{
			syntax_error("empty command before pipe");
			return (-1); // how to hanlde the error?
		}
		(*current)->next = cmd_new();
		(*current) = (*current)->next;
		state = EXPECT_COMMAND;
	}
	else
	{
		syntax_error("unexpected token");
		return (-1); // how to hanlde the error?
	}
	return (state);
}

int	handle_command(int state, t_cmd **current, int *last_redir, 
	t_token *tokens, t_cmd **head)
{
	if (tokens->type == WORD)
	{
		if (!*current)
			init_command(head, current);
		(*current)->cmd = tokens->value;
		if (!argv_add(*current, tokens->value))
			return (-1); // error?
		state = EXPECT_ARG_OR_REDIR;
	}
	else if (tokens->type >= REDIR_OUT && tokens->type <= HEREDOC)
	{
		if (!*current)
			init_command(head, current);
		*last_redir = tokens->type;
		state = EXPECT_REDIR_TARGET;
	}
	else
	{
		syntax_error("unexpected/wrong token");
		return (-1) ; // how to hanlde the error?
	}
	return (state);
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
			state = handle_command(state, &current, &last_redir, tokens, &head);
		else if (state == EXPECT_ARG_OR_REDIR)
			state = handle_arg_or_redir(state, &current, &last_redir, tokens);
		else if (state == EXPECT_REDIR_TARGET)
			state = handle_redir_target(state, &current, &last_redir, tokens);
		tokens = tokens->next;
	}
	if (state == EXPECT_REDIR_TARGET)
	{
		syntax_error("unexpected end of input; WORD needed");
		return (NULL);
	}
	return (head);
}
